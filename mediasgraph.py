import matplotlib.pyplot as plt

# Dados medidos pelo sensor
umidades = [
    46.83, 45.83, 45.00, 45.33, 45.60, 45.60, 46.23, 45.90, 45.00, 44.80,
    44.00, 44.00, 44.00, 44.00, 44.10, 44.07, 43.33, 43.00, 43.00, 43.00, 
    43.00, 43.30, 43.00, 44.06
]
temperaturas = [
    30.98, 30.76, 30.56, 30.24, 30.06, 29.88, 29.80, 29.82, 29.70, 29.55,
    29.46, 29.31, 29.22, 29.11, 29.05, 28.99, 28.92, 28.83, 28.80, 28.77,
    28.69, 28.69, 28.69, 27.56
]

# Gerando os tempos (1 minuto para cada medição, última após 10 minutos)
tempos = list(range(1, len(umidades))) + [len(umidades) + 9]  # Último intervalo é após 10 minutos

# Plotando o gráfico
plt.figure(figsize=(10, 6))

# Gráficos de temperatura e umidade
plt.plot(tempos, temperaturas, 'o-', color='red', label='Temperatura (°C)')
plt.plot(tempos, umidades, 'o-', color='blue', label='Umidade (%)')

plt.title('Médias de Temperatura e Umidade ao Longo do Tempo', fontsize=16)
plt.xlabel('Tempo (minutos)', fontsize=12)
plt.ylabel('Valores', fontsize=12)
plt.grid(True)
plt.legend()

# Exibir o gráfico
plt.show()
