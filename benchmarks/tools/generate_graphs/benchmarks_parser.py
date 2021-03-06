import re
import visualize
import json, io, sys
from typing import List, Dict, Optional, Any, TypedDict

Heuristics = TypedDict("Heuristics", {"max": float, "min": float}, total=False)
ParsedBenchmark = TypedDict("ParsedBenchmark", {
    "category": visualize.category_info,
    "error": Dict[str, str],
    "name": str,
    "run_names": List[str],
    "data": Dict[str, Dict[str, List[float]]],
    "statistics": Dict[str, Dict[str, Dict[str, float]]],
    "heuristics": Heuristics
},
                            total=False)


def len_sorter(x):
	return len(x)


def data_group_name_sorter(dg: visualize.data_group):
	if dg.is_noop_group:
		return ""
	if dg.error is not None:
		return ""
	return dg.name


def data_group_mean_sorter(dg: visualize.data_group):
	if dg.error is not None:
		return sys.float_info.max
	mean_group = dg.labels[dg.primary_label]
	return mean_group.stats.mean


def category_sorter(c: visualize.category_info):
	# shortest name wins
	return c.name


def match_category(c: visualize.category_info, name: str) -> bool:
	s = c.pattern.search(name)
	if s != None:
		e = c.exclude_pattern.search(name)
		if e != None:
			return False
		else:
			return True
	else:
		return False


def match_target(b: ParsedBenchmark, name: str) -> bool:
	if name in b['run_names']:
		return True
	return match_category(b['category'], name)


def parse_benchmark(b: ParsedBenchmark, category: visualize.category_info,
                    analysis: visualize.analysis_info,
                    noop_benches: Optional[visualize.benchmark]) -> visualize.benchmark:
	run_labels: List[visualize.data_group] = []
	for run_name in b["run_names"]:
		named_data = b["data"][run_name]
		run_label: Dict[str, visualize.data_label] = {}
		maybe_primary_group_labels = [dli for dli in analysis.data_labels if dli.primary]
		primary_label_info: visualize.data_label_info = maybe_primary_group_labels[0] if len(
		    maybe_primary_group_labels) > 0 else analysis.data_labels[0]
		primary_label_id: str = primary_label_info.id
		for data_id in named_data:
			data_info = [dli for dli in analysis.data_labels if dli.id == data_id][0]
			run_label[data_id] = visualize.data_label(data_id, analysis, data_info,
			                                          named_data[data_id])
		group_name: str = run_name
		m: re.Match = category.pattern.search(group_name)
		is_whole_group_name: bool = (m.start() == 0
		                             and m.end() == len(group_name)) if m is not None else False
		if m is not None and not is_whole_group_name:
			group_name = group_name[:m.start()] + group_name[m.end():]
		for prefix in analysis.prefixes_to_remove:
			group_name = group_name.removeprefix(prefix)
		for suffix in analysis.suffixes_to_remove:
			group_name = group_name.removesuffix(suffix)
		group = visualize.data_group(group_name, category, run_label, primary_label_id)
		run_labels.append(group)
	if noop_benches is visualize.benchmark:
		run_labels.append(noop_benches.groups[0])
	heuristics: visualize.stats = visualize.stats([])
	heuristics.max = b["heuristics"]["max"]
	heuristics.min = b["heuristics"]["min"]
	benchmark: visualize.benchmark = visualize.benchmark(category, analysis, run_labels,
	                                                     heuristics)
	return benchmark


def aggregate_categories(all_benchmarks_data: List[ParsedBenchmark],
                         analysis: visualize.analysis_info) -> List[visualize.benchmark]:

	all_benchmarks: List[visualize.benchmark] = []

	# find no-op category if it exists
	noop_benches: Optional[visualize.benchmark] = None
	for b in all_benchmarks_data:
		maybe_noop_category_info: visualize.category_info = b["category"]
		if visualize.is_noop_category(maybe_noop_category_info.name):
			noop_benches = parse_benchmark(b, maybe_noop_category_info, analysis, None)
			break

	for b in all_benchmarks_data:
		category_info: visualize.category_info = b["category"]
		if visualize.is_noop_category(category_info.name):
			continue

		benchmark: visualize.benchmark = parse_benchmark(b, category_info, analysis, noop_benches)
		all_benchmarks.append(benchmark)

	for benchmark in all_benchmarks:
		lower_is_better: bool = (benchmark.category.order == visualize.category_order.ascending)
		# first, sort by name so we can assign colors to each
		# benchmark appropriately (and make those
		# color assignments stable)
		groups = benchmark.groups
		groups.sort(key=data_group_name_sorter)
		for name_index, data_group in enumerate(groups):
			data_group.name_index = name_index

		# then, sort by mean
		groups.sort(key=data_group_mean_sorter, reverse=lower_is_better)

	return all_benchmarks


def parse_benchmarks_json_into(j: Any, info: visualize.analysis_info,
                               all_benchmarks: List[ParsedBenchmark]):
	j_benchmarks_array = j["benchmarks"]
	for j_benchmark in j_benchmarks_array:
		run_name: str = j_benchmark['run_name']

		if info.categories == None:
			raise Exception(
			    "no categories to work with: define at least one category in the JSON config")

		potential_categories = [c for c in info.categories if match_category(c, run_name)]
		if len(potential_categories) < 1:
			raise Exception("no categories matched the given benchmark run from the config")

		potential_categories.sort(key=category_sorter)
		category: visualize.category_info = potential_categories[0]
		benchmark_name = category.name

		potential_targets = [b for b in all_benchmarks if match_target(b, run_name)]
		if (len(potential_targets) == 1):
			pass
		elif len(potential_targets) > 1:
			# we have a problem here?
			raise Exception("too many potential targets")
		else:
			all_benchmarks.append({
			    "category": category,
			    "name": benchmark_name,
			    "run_names": [run_name],
			    "data": {},
			    "statistics": {},
			    "heuristics": {
			        "max": sys.float_info.min,
			        "min": sys.float_info.max
			    }
			})
			potential_targets = [all_benchmarks[-1]]

		benchmark: ParsedBenchmark = potential_targets[-1]
		# check for errors
		benchmark_error = j_benchmark.get('error_occurred')
		if benchmark_error != None and benchmark_error:
			benchmark["error"] = j_benchmark['error_message']
			continue

		# populate data
		category_data: Dict[str, Dict[str, List[float]]] = benchmark["data"]
		heuristics: Heuristics = benchmark['heuristics']
		category_statistics = benchmark["statistics"]
		if run_name not in category_data:
			category_data[run_name] = {}
		if run_name not in category_statistics:
			category_statistics[run_name] = {}

		run_names: List[str] = benchmark['run_names']
		data: Dict[str, List[float]] = category_data[run_name]
		statistics: Dict[str, Dict[str, float]] = category_statistics[run_name]

		if not run_name in run_names:
			run_names.append(run_name)

		time_unit = j_benchmark['time_unit']
		primary_data_label: visualize.data_label_info = info.data_labels[0]
		for data_label in info.data_labels:
			point_id = data_label.id
			if point_id not in data:
				data[point_id] = []

		j_benchmark_run_type: str = j_benchmark["run_type"]
		if j_benchmark_run_type == "iteration":
			# is a data point
			for data_label in info.data_labels:
				to_seconds_multiplier: float = 1
				if data_label.format == visualize.data_label_format.clock:
					time_scale = primary_data_label.get_scale_by_abbreviation(time_unit)
					to_seconds_multiplier = time_scale.from_unit_scale
				else:
					raise NotImplementedError()
				point_id = data_label.id
				point_list = data[point_id]
				point = j_benchmark[point_id]
				point_adjusted = point * to_seconds_multiplier
				point_list.append(point_adjusted)
				heuristics["min"] = min(heuristics["min"], point_adjusted)
				heuristics["max"] = max(heuristics["max"], point_adjusted)
		elif j_benchmark_run_type == "aggregate":
			# is a statistic or aggregate of some sort
			j_benchmark_aggregate_name: str = j_benchmark["aggregate_name"]
			if j_benchmark_aggregate_name not in statistics:
				statistics[j_benchmark_aggregate_name] = {}
			statistic: Dict[str, float] = statistics[j_benchmark_aggregate_name]
			for data_label in info.data_labels:
				point_id = data_label.id
				point = j_benchmark[point_id]
				point_adjusted = point * to_seconds_multiplier
				statistic[point_id] = point_adjusted


def parse_benchmarks_from_sources(info: visualize.analysis_info) -> List[visualize.benchmark]:
	all_benchmarks: List[ParsedBenchmark] = []
	successfully_opened: int = 0
	for src_info in info.sources:
		try:
			with io.open(src_info.file_name) as f:
				j = json.load(f)
				parse_benchmarks_json_into(j, info, all_benchmarks)
				successfully_opened += 1
		except FileNotFoundError as e:
			if src_info.required:
				raise e
		except Exception as e:
			raise e

	if successfully_opened < 1 and info.at_least_one_required:
		raise Exception("at least one source file was required but it was not provided")

	return aggregate_categories(all_benchmarks, info)
