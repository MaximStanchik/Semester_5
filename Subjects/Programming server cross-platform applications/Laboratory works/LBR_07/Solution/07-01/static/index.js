document.addEventListener('DOMContentLoaded', function() {
    
    const loadJSON = async function () {
        try {
            const response = await fetch ('index.json');
            if (!response.ok) {
                throw new Error ('Ошибка загрузки JSON');
            }
            const data = await response.json();
            document.getElementById('json-output').textContent = JSON.stringify(data, null, 2);

        }
        catch (error) {
            console.error(error);
            document.getElementById('json-output').textContent = 'Ошибка при результате JSON: ' + error.message;
        }
    }

    const loadXML = async function () {
        try {
            const response = await fetch ('index.xml');
            if (!response.ok) {
                throw new Error ('Ошибка загрузки XML');
            }
            const text = await response.text(); 
            const parser = new DOMParser(); 
            const xmlDoc = parser.parseFromString(text, 'text/xml'); 
            const xmlString = new XMLSerializer().serializeToString(xmlDoc); 
            document.getElementById('xml-output').textContent = xmlString;
        }
        catch (error) {
            console.error(error);
            document.getElementById('xml-output').textContent = 'Ошибка при результате XML: ' + error.message;
        }
    }

    loadJSON();
    loadXML();
})