import requests
import pytest


BASE_URL = "https://jsonplaceholder.typicode.com"

# Фикстура для подготовки данных
@pytest.fixture(scope="module")
def setup():
    pass

# Позитивный тест: Проверка доступности всех пользователей
def test_get_users():
    response = requests.get(f"{BASE_URL}/users")
    assert response.status_code == 200
    assert len(response.json()) > 0  # Проверяем, что список пользователей не пустой

