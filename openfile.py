import os
import json
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend

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

# Функция для чтения зашифрованных данных из файла
def load_encrypted_tracks(filename):
    with open(filename, 'rb') as file:
        # Первые 16 байт - это IV
        iv = file.read(16)
        # Остальные байты - зашифрованные данные
        encrypted_data = file.read()
    return iv, encrypted_data

# Пример: путь к файлу с зашифрованными треками
filename = 'encrypted_tracks.bin'

# Пример: ключ для дешифровки (нужно использовать тот же ключ, который использовался для шифрования)
key = os.urandom(32)  # Важно! Ключ должен быть точно таким же, как при шифровании

# Читаем зашифрованные данные из файла
iv, encrypted_tracks = load_encrypted_tracks(filename)

# Дешифруем GPS треки
try:
    decrypted_tracks = decrypt_gps_tracks(iv, encrypted_tracks, key)
    print("Расшифрованные GPS треки:", decrypted_tracks)
except Exception as e:
    print("Не удалось расшифровать данные. Проверьте правильность ключа.")