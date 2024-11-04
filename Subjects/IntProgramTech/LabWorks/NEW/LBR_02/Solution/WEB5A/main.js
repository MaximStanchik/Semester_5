document.getElementById('sendRequestXY').addEventListener('click', function() {
    const valueX = document.getElementById('valueX').value;
    const valueY = document.getElementById('valueY').value;

    const xhr = new XMLHttpRequest();
    xhr.open('POST', 'http://localhost:3000/submitXY', true); 
    xhr.setRequestHeader('X-Value-x', valueX);
    xhr.setRequestHeader('X-Value-y', valueY);
    xhr.onreadystatechange = function() {
        if (xhr.readyState === 4) { 
            if (xhr.status === 200) {
                const response = JSON.parse(xhr.responseText);
                document.getElementById('resultZ').innerText = response.z; 
            } else {
                document.getElementById('resultZ').innerText = 'Ошибка: ' + xhr.statusText;
            }
        }
    };
    xhr.send();
});