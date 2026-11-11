from pathlib import Path

import matplotlib.pyplot as plt


def plot_speedups(
    x_values,
    quicksort_speedup,
    parallel_sort_speedup,
    title,
    x_label,
    output_filename,
    logarithmic_x_axis=False,
    x_tick_labels=None,
):
    fig, ax = plt.subplots(figsize=(9, 5))
    ax.plot(
        x_values,
        quicksort_speedup,
        marker="o",
        label="min_max_quicksort",
    )
    ax.plot(
        x_values,
        parallel_sort_speedup,
        marker="o",
        label="gnu_parallel::sort",
    )
    ax.set(
        title=title,
        xlabel=x_label,
        ylabel="Speedup over std::sort",
        xticks=x_values,
    )
    if logarithmic_x_axis:
        ax.set_xscale("log")
    if x_tick_labels:
        ax.set_xticklabels(x_tick_labels)
    ax.grid(True, alpha=0.3)
    ax.legend()
    fig.tight_layout()

    output_path = Path(__file__).with_name(output_filename)
    fig.savefig(output_path, dpi=200)
    print(f"Plot saved to {output_path}")


if __name__ == "__main__":
    thread_num = list(range(1, 21))
    thread_num_quicksort_speedup = [
        0.756994, 1.4787, 2.108, 2.65445, 3.10027,
        3.48117, 3.70076, 3.96337, 4.11289, 4.25746,
        4.41725, 4.53345, 4.62462, 4.78413, 4.87718,
        4.89836, 5.03526, 5.09275, 5.14455, 5.24298,
    ]
    thread_num_parallel_sort_speedup = [
        0.983415, 1.86477, 2.83106, 3.79219, 4.54961,
        5.25346, 4.99816, 5.67113, 6.12391, 6.658,
        7.30169, 7.76985, 8.29442, 8.72047, 9.43217,
        9.9377, 10.4365, 11.0639, 11.3048, 12.013,
    ]
    array_size = [100000, 1000000, 10000000, 100000000]
    array_size_quicksort_speedup = [3.89468, 4.64768, 5.1518, 5.71326]
    array_size_parallel_sort_speedup = [6.88574, 11.278, 11.1096, 10.9503]

    plot_speedups(
        thread_num,
        thread_num_quicksort_speedup,
        thread_num_parallel_sort_speedup,
        "Sorting speedup by number of threads (array size $10^7$)",
        "Number of threads",
        "thread_num_speedup.png",
    )
    plot_speedups(
        array_size,
        array_size_quicksort_speedup,
        array_size_parallel_sort_speedup,
        "Sorting speedup by array size (20 threads)",
        "Array size",
        "array_size_speedup.png",
        logarithmic_x_axis=True,
        x_tick_labels=[f"{size:,}" for size in array_size],
    )
