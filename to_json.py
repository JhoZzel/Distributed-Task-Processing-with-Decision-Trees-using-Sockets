import csv
import json

# Lee el archivo CSV y conviértelo a JSON
csv_file = "a.csv"
json_file = "a.json"

# Lista para almacenar los datos
data = []

# Abre el archivo CSV y lee sus contenidos
with open(csv_file, 'r') as file:
    csv_reader = csv.reader(file)
    headers = next(csv_reader)  # Lee la primera fila como encabezados

    # Itera sobre las filas restantes del CSV
    for row in csv_reader:
        # Crea un diccionario para cada fila
        item = {}
        for i in range(len(headers)):
            # Asigna cada valor a su respectivo encabezado
            item[headers[i]] = float(row[i]) if row[i].replace('.', '').isdigit() else row[i]
        data.append(item)

# Escribe los datos en un archivo JSON
with open(json_file, 'w') as file:
    json.dump(data, file, indent=4)

print(f"Se ha creado el archivo JSON: {json_file}")

