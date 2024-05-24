import multiprocessing

def generate_series(start, end, step):
    return [i for i in range(start, end + 1, step)]

if __name__ == "__main__":
    M = 4  # Número de procesadores
    N = 20  # Número de términos en la serie

    chunk_size = N // M
    tasks = []

    # Crear tareas para cada procesador
    for i in range(M):
        start = i * chunk_size * 2 + 2
        end = start + (chunk_size * 2 - 2)
        tasks.append((start, end, 2))

    with multiprocessing.Pool(processes=M) as pool:
        results = pool.starmap(generate_series, tasks)

    # Combinar los resultados de todos los procesos
    combined_results = [item for sublist in results for item in sublist]

    # Mostrar la serie generada
    print(combined_results)
