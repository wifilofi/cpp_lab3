#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np

def main() -> None:
    try:
        with open("cmake-build-debug/quick_results.txt") as f:
            quick_times = [float(x) for x in f.read().split() if x.strip()]

        with open("cmake-build-debug/insertion_results.txt") as f:
            insertion_times = [float(x) for x in f.read().split() if x.strip()]
    except FileNotFoundError as e:
        print(f"Тхтшник не найден {e}")
        return

    if not quick_times or not insertion_times:
        print("Некорректн содержание тхтшников")
        return

    best_threshold = 16
    best_ratio = float('inf')

    for i in range(10, min(31, len(insertion_times), len(quick_times))):
        if insertion_times[i] > 0 and quick_times[i] > 0:
            ratio = insertion_times[i] / quick_times[i]
            if ratio < best_ratio:
                best_ratio = ratio
                best_threshold = i

    limit = min(51, len(quick_times), len(insertion_times))
    x = np.arange(0, limit, 1, dtype=int)

    plt.figure(figsize=(10, 6))

    plt.plot(x, quick_times[:limit], "b-", linewidth=2, label="Быстрая сортировка (quick sort)")
    plt.plot(x, insertion_times[:limit], "g-", linewidth=2, label="Сортировка вставками (insertion sort)")

    if 0 < best_threshold < limit:
        plt.axvline(x=best_threshold, color='red',
                    alpha=0.7, label=f'Оптимальный порог: {best_threshold}')


    plt.xticks(x[::2])

    plt.title("Сравнение скорости сортировок на массивах разных размеров")
    plt.xlabel("Размер массива")
    plt.ylabel("Время выполнения, нс")
    plt.legend()
    plt.grid(True, alpha=0.3)

    plt.tight_layout()
    plt.margins(x=0.01)

    plt.savefig('sorting_comparison.png', dpi=150)
    plt.show()


if __name__ == "__main__":
    main()
