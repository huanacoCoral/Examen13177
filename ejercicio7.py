import multiprocessing
import random

def is_inside_circle(_):
    x = random.uniform(0, 1)
    y = random.uniform(0, 1)
    return x * x + y * y <= 1

def calculate_pi(num_points):
    with multiprocessing.Pool() as pool:
        points_inside_circle = sum(pool.map(is_inside_circle, range(num_points)))
    return (4.0 * points_inside_circle) / num_points

if __name__ == "__main__":
    num_points = 1000000  # Número de puntos a generar
    pi_estimate = calculate_pi(num_points)
    print(f"Estimación de PI: {pi_estimate}")
