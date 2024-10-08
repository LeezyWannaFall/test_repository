import os
import json
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend

# Функция для шифрования GPS координат
def encrypt_gps_track(gps_track, key):
    track_data = json.dumps(gps_track).encode('utf-8')
    
    # Генерируем случайный вектор инициализации (IV)
    iv = os.urandom(16)
    
    # Создаем объект AES в режиме CBC
    cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend())
    encryptor = cipher.encryptor()
    
    # Выравниваем данные до размера блока AES (16 байт) с нулями
    padding_len = 16 - (len(track_data) % 16)
    padded_data = track_data + bytes([padding_len] * padding_len)
    
    # Шифруем данные
    encrypted_data = encryptor.update(padded_data) + encryptor.finalize()
    
    # Возвращаем зашифрованные данные и IV
    return iv, encrypted_data

# Функция для дешифровки GPS треков
def decrypt_gps_track(iv, encrypted_data, key):
    cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend())
    decryptor = cipher.decryptor()
    
    decrypted_data = decryptor.update(encrypted_data) + decryptor.finalize()
    
    padding_len = decrypted_data[-1]
    decrypted_data = decrypted_data[:-padding_len]
    
    gps_track = json.loads(decrypted_data.decode('utf-8'))
    
    return gps_track

# Ввод GPS координат пользователем
def input_coordinates():
    latitude = float(input("Введите широту (latitude): "))
    longitude = float(input("Введите долготу (longitude): "))
    
    gps_track = [{"latitude": latitude, "longitude": longitude}]
    
    return gps_track

# Пример использования
def main():
    # Ключ для шифрования (должен быть 16, 24 или 32 байта для AES)
    key = os.urandom(32)
    
    # Ввод координат
    gps_track = input_coordinates()

    # Шифрование координат
    iv, encrypted_track = encrypt_gps_track(gps_track, key)
    
    # Вывод зашифрованных данных
    print(f"Зашифрованные GPS координаты: {encrypted_track.hex()}")
    
    # Дешифрование для проверки
    decrypted_track = decrypt_gps_track(iv, encrypted_track, key)
    print(f"Расшифрованные GPS координаты: {decrypted_track}")

if __name__ == "__main__":
    main()
