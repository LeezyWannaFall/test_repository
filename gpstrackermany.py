import os
import json
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend

# Функция для шифрования GPS треков
def encrypt_gps_tracks(gps_tracks, key):
    # Преобразуем список GPS треков в строку JSON
    tracks_data = json.dumps(gps_tracks).encode('utf-8')
    
    # Генерируем случайный вектор инициализации (IV)
    iv = os.urandom(16)
    
    # Создаем объект AES в режиме CBC
    cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend())
    
    encryptor = cipher.encryptor()
    
    # Выравниваем данные до размера блока AES (16 байт) с нулями
    padding_len = 16 - (len(tracks_data) % 16)
    padded_data = tracks_data + bytes([padding_len] * padding_len)
    
    # Шифруем данные
    encrypted_data = encryptor.update(padded_data) + encryptor.finalize()
    
    # Возвращаем зашифрованные данные и IV
    return iv, encrypted_data

# Функция для дешифровки GPS треков
def decrypt_gps_tracks(iv, encrypted_data, key):
    # Создаем объект AES для дешифрования
    cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend())
    decryptor = cipher.decryptor()
    
    # Дешифруем данные
    decrypted_data = decryptor.update(encrypted_data) + decryptor.finalize()
    
    # Убираем дополнение (padding)
    padding_len = decrypted_data[-1]
    decrypted_data = decrypted_data[:-padding_len]
    
    # Преобразуем обратно в формат JSON
    gps_tracks = json.loads(decrypted_data.decode('utf-8'))
    
    return gps_tracks

# Функция для записи зашифрованных данных в файл
def save_encrypted_tracks(filename, iv, encrypted_data):
    with open(filename, 'wb') as file:
        # Сначала записываем IV, потом зашифрованные данные
        file.write(iv + encrypted_data)

# Функция для чтения зашифрованных данных из файла
def load_encrypted_tracks(filename):
    with open(filename, 'rb') as file:
        # Первые 16 байт - это IV
        iv = file.read(16)
        # Остальные байты - зашифрованные данные
        encrypted_data = file.read()
    return iv, encrypted_data

# Пример нескольких GPS треков (широта и долгота)
gps_tracks = [
    [
        {"latitude": 51.5074, "longitude": -0.1278},  # Лондон
        {"latitude": 48.8566, "longitude": 2.3522},   # Париж
        {"latitude": 40.7128, "longitude": -74.0060}  # Нью-Йорк
    ],
    [
        {"latitude": 35.6895, "longitude": 139.6917},  # Токио
        {"latitude": 37.7749, "longitude": -122.4194}, # Сан-Франциско
        {"latitude": 55.7558, "longitude": 37.6176}    # Москва
    ]
]

# Ключ должен быть 16, 24 или 32 байта (например, 32 для AES-256)
key = os.urandom(32)

# Шифруем GPS треки
iv, encrypted_tracks = encrypt_gps_tracks(gps_tracks, key)

# Сохраняем зашифрованные треки в файл
save_encrypted_tracks('encrypted_tracks.bin', iv, encrypted_tracks)
print("Зашифрованные GPS треки успешно записаны в файл.")

# Для проверки читаем зашифрованные данные из файла и дешифруем их
iv_loaded, encrypted_tracks_loaded = load_encrypted_tracks('encrypted_tracks.bin')
decrypted_tracks = decrypt_gps_tracks(iv_loaded, encrypted_tracks_loaded, key)

# Выводим расшифрованные треки для проверки
print("Расшифрованные GPS треки:", decrypted_tracks)