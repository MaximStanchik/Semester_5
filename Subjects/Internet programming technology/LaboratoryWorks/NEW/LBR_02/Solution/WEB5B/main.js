document.getElementById('sendRequest').addEventListener('click', function() {
    const valueN = document.getElementById('valueN').value;

    fetch('http://localhost:3000/submit', {
        method: 'POST',
        headers: {
            'X-Rand-N': valueN
        }
    })
    .then(response => {
        if (response.ok) {
            return response.json(); 
        } else {
            return response.text().then(text => {
                document.getElementById('resultNumbers').innerText = 'Ошибка: ' + text;
            });
        }
    })
    .then(data => {
        document.getElementById('resultNumbers').innerText = JSON.stringify(data);
    })
    .catch(error => {
        console.error('Ошибка:', error);
        document.getElementById('resultNumbers').innerText = 'Ошибка при отправке запроса';
    });
});