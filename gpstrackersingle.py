from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
import os
import json


def encrypt_gps_track(gps_track, key):
    track_data = json.dumps(gps_track).encode('utf-8')
    iv = os.urandom(16)
    cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend())
    encryptor = cipher.encryptor()
    
    padding_len = 16 - (len(track_data) % 16)
    padded_data = track_data + bytes([padding_len] * padding_len)
    
    encrypted_data = encryptor.update(padded_data) + encryptor.finalize()
    return iv, encrypted_data

def decrypt_gps_track(iv, encrypted_data, key):
    cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend())
    decryptor = cipher.decryptor()
    decrypted_data = decryptor.update(encrypted_data) + decryptor.finalize()
    padding_len = decrypted_data[-1]
    decrypted_data = decrypted_data[:-padding_len]
    gps_track = json.loads(decrypted_data.decode('utf-8'))
    
    return gps_track


gps_track = [
    {"latitude": 51.5074, "longitude": -0.1278},  # Лондон
    {"latitude": 48.8566, "longitude": 2.3522},   # Париж
    {"latitude": 40.7128, "longitude": -74.0060}  # Нью-Йорк
]
key = os.urandom(32)

iv, encrypted_track = encrypt_gps_track(gps_track, key)
print(f"Зашифрованный GPS трек: {encrypted_track.hex()}")

decrypted_track = decrypt_gps_track(iv, encrypted_track, key)
print(f"Расшифрованный GPS трек: {decrypted_track}")