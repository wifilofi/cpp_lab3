#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np

def main() -> None:
    try:
        with open("cmake-build-debug/quick_results.txt") as f:
            quick_times = [float(x) for x in f.read().split() if x.strip()]
        with open("cmake-build-debug/insertion_results.txt") as f:
            insertion_times = [float(x) for x in f.read().split() if x.strip()]
        with open("cmake-build-debug/hybrid_results.txt") as f:
            hybrid_times = [float(x) for x in f.read().split() if x.strip()]
    except FileNotFoundError as e:
        print(f"Ошибка: {e}")
        return

    if not quick_times or not insertion_times or not hybrid_times:
        print("Некорректные данные в файлах")
        return

    best_threshold = 16
    best_ratio = float('inf')
    for i in range(10, min(31, len(insertion_times), len(quick_times))):
        if insertion_times[i] > 0 and quick_times[i] > 0:
            ratio = insertion_times[i] / quick_times[i]
            if ratio < best_ratio:
                best_ratio = ratio
                best_threshold = i

    print(f"Оптимальный порог: {best_threshold} элементов")

    plt.figure(figsize=(10, 6))

    limit = min(51, len(quick_times), len(insertion_times), len(hybrid_times))
    x = np.arange(0, limit, 1, dtype=int)

    plt.plot(x, quick_times[:limit], "b-", linewidth=2, label="Quick Sort")
    plt.plot(x, insertion_times[:limit], "g--", linewidth=2, label="Insertion Sort")
    plt.plot(x, hybrid_times[:limit], "r-", linewidth=2, label="Hybrid Sort")
    plt.xlabel("Размер массива")
    plt.ylabel("Время выполнения, нс")
    plt.title("Сравнение трёх алгоритмов сортировки")
    plt.legend()
    plt.grid(True, alpha=0.3)

    if best_threshold < len(hybrid_times):
        print(f"Гибридная сортировка на {best_threshold} элементах: {hybrid_times[best_threshold]:.1f} нс")

    plt.tight_layout()
    plt.savefig('sorting_comparison.png', dpi=150)
    plt.show()


if __name__ == "__main__":
    main()