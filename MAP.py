import sys
from tokenize import Double

MAX = 1000
idx = 0
data = ["" for _ in range(MAX)]
graph = [[0.0 for _ in range(MAX)] for _ in range(MAX)]

def menu():
    print("Welcome to MAPS\n\n")
    print("[--PROGRAM MENU--]--\n\n")
    print("1. Tambah Lokasi\n")
    print("2. Cari Rute\n")
    print("3. EXIT\n")

def compare_strings(str1, str2):
    return str1.lower() == str2.lower()

def find_idx(kota):
    global idx
    for i in range(idx):
        if compare_strings(kota, data[i]):
            return i
    data[idx] = kota
    idx += 1
    return idx - 1

def found(kota):
    global idx
    for i in range(idx):
        if compare_strings(kota, data[i]):
            return i
    return -1

def add():
    global idx
    lokasi1, lokasi2 = -1, -2
    kota1 = ""
    kota2 = ""
    while True:
        kota1 = input("Input Lokasi pertama ")
        kota2 = input("Input Lokasi kedua ")
        if compare_strings(kota1, kota2):
            print("Lokasi 1 dan 2 tidak boleh mempunya nama yang sama, mohon input ulang\n")
        else:
            break

    lokasi1 = find_idx(kota1)
    lokasi2 = find_idx(kota2)

    jarak = float(input("Input jarak antar 2 lokasi tersebut (input berupa angka)(km) "))

    graph[lokasi1][lokasi2] = jarak
    graph[lokasi2][lokasi1] = jarak

    print("\njarak antara", data[lokasi1], "dan", data[lokasi2], "sejauh", graph[lokasi2][lokasi1], "km sudah ditambahkan ke data!\n\n")

def printall():
    global idx
    if idx == 0:
        print("\nDATA EMPTY!\n\n")
        return
    else:
        print("DATA\n")
        for i in range(idx):
            for j in range(idx):
                if graph[i][j] == 0:
                    continue
                print(data[i], "ke", data[j], "=", graph[i][j], "km")

def print_path(current_vertex, parents):
    if current_vertex == -1:
        return
    print_path(parents[current_vertex], parents)
    print(data[current_vertex], "->", end=" ")

def print_solution(distances, parents, end):
    print_path(end, parents)
    print(distances[end], "km")

def dijkstra(start, end):
    shortest_distances = [float("inf") for _ in range(idx)]
    added = [False for _ in range(idx)]
    for vertex_index in range(idx):
        shortest_distances[vertex_index] = float("inf")
        added[vertex_index] = False
    shortest_distances[start] = 0
    parents = [-1 for _ in range(idx)]
    parents[start] = -1
    for _ in range(1, idx):
        nearest_vertex = -1
        shortest_distance = float("inf")
        for vertex_index in range(idx):
            if not added[vertex_index] and shortest_distances[vertex_index] < shortest_distance:
                nearest_vertex = vertex_index
                shortest_distance = shortest_distances[vertex_index]
        added[nearest_vertex] = True
        for vertex_index in range(idx):
            edge_distance = graph[nearest_vertex][vertex_index]
            if edge_distance > 0 and (shortest_distance + edge_distance) < shortest_distances[vertex_index]:
                parents[vertex_index] = nearest_vertex
                shortest_distances[vertex_index] = shortest_distance + edge_distance
    print_solution(shortest_distances, parents, end)
    return shortest_distances[end]

def cari():
    global idx
    if idx == 0:
        return
    lokasi1, lokasi2 = -1, -2
    kota1, kota2 = "", ""
    while True:
        kota1 = input("Input Start ")
        kota2 = input("Input Finish ")
        lokasi1 = found(kota1)
        lokasi2 = found(kota2)
        if compare_strings(kota1, kota2) or lokasi1 == -1 or lokasi2 == -1:
            print("Lokasi tidak ada di data\n")
            printall()
        else:
            break
    lokasi1 = find_idx(kota1)
    lokasi2 = find_idx(kota2)
    kendaraan = input("Kendaraan apa yang dipakai (motor{50km/jam}/mobil{80km/jam})? ")
    while kendaraan.lower() not in ["motor", "mobil"]:
        kendaraan = input("Input kendaraan yang sesuai(motor/mobil) ")
    print("")
    time = dijkstra(lokasi1, lokasi2)
    print("dengan", kendaraan, "akan memakan waktu selama", end=" ")
    if kendaraan.lower() == "motor":
        time = time / 50
    else:
        time = time / 80
    if time >= 1:
        print(int(time), "jam", end=" ")
        time -= int(time)
    print(float(time * 60), "menit")

def main():
    while True:
        menu()
        input_ = input("Pilih Opsi(1-3) ")
        while input_[0] > '3' or input_[0] < '1' or len(input_) != 1:
            menu()
            print("Mohon masukan input yang benar(1-3) ")
            input_ = input("Pilih Opsi(1-3) ")
        if input_[0] == '1':
            add()
        elif input_[0] == '2':
            printall()
            cari()
        elif input_[0] == '3':
            print("goodbye :(")
            sys.exit(0)

if __name__ == "__main__":
    main()
