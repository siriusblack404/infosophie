#!/usr/bin/env python3
import os
import shutil
import sqlite3

def dump_chrome_passwords():
    login_db = os.path.expanduser('~/.config/google-chrome/Default/Login Data')
    if not os.path.exists(login_db):
        print("Login Data not found")
        return

    # Copie pour éviter les locks
    shutil.copy2(login_db, 'LoginDataCopy.db')

    conn = sqlite3.connect('LoginDataCopy.db')
    cursor = conn.cursor()
    cursor.execute('SELECT origin_url, username_value FROM logins')
    for row in cursor.fetchall():
        url = row[0]
        username = row[1]
        print(f'URL: {url}')
        print(f'User: {username}')
        print('Password: [non déchiffré dans cette version]')
        print('-' * 20)

    conn.close()
    os.remove('LoginDataCopy.db')

if __name__ == '__main__':
    dump_chrome_passwords()
