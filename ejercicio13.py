import multiprocessing

# Función para calcular el término de Fibonacci
def fibonacci(n):
    if n <= 1:
        return n
    else:
        return fibonacci(n-1) + fibonacci(n-2)

if __name__ == "__main__":
    # Número total de términos de Fibonacci que queremos calcular
    total_terms = 1000
    
    # Número de procesadores disponibles
    num_processors = multiprocessing.cpu_count()
    
    # Calcular cuántos términos de Fibonacci calculará cada proceso
    terms_per_process = total_terms // num_processors
    
    # Lista para almacenar los resultados
    results = []
    
    # Función para calcular los términos de Fibonacci en paralelo
    def calculate_fibonacci_range(start, end):
        return [fibonacci(i) for i in range(start, end)]

    # Crear un pool de procesos
    with multiprocessing.Pool(processes=num_processors) as pool:
        # Calcular términos de Fibonacci en paralelo para cada rango
        for i in range(num_processors):
            start = i * terms_per_process
            end = (i + 1) * terms_per_process if i < num_processors - 1 else total_terms
            results.extend(pool.apply(calculate_fibonacci_range, args=(start, end)))

    # Imprimir los resultados
    print("Los primeros 1000 términos de Fibonacci son:")
    print(results)
