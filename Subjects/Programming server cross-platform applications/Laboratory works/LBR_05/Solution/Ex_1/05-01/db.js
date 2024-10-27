const EventEmitter = require('events');

class DatabaseCRUD extends EventEmitter {
    constructor() {
        super();
        this.data = [
            { id: 1, name: 'Иван', bday: '1990-01-01' },
            { id: 2, name: 'Мария', bday: '1992-05-15' },
            { id: 3, name: 'Сергей', bday: '1988-10-30' }
        ];
    }

    validateDate(bday) {
        const date = new Date(bday);
        const today = new Date();
        today.setHours(0, 0, 0, 0);
        if (isNaN(date.getTime()) || date > today) {
            throw new Error('Некорректная дата рождения или дата в будущем');
        }
    }

    validateEntry(entry) {
        if (!entry.name || !entry.bday) {
            throw new Error('Имя и дата рождения обязательны');
        }
        this.validateDate(entry.bday); 
    }

    select() {
        this.emit('GET', this.data);
        return this.data;
    }

    insert(entry) {
        this.validateEntry(entry);
        let newId;
        if (this.data.length > 0) {
            newId = this.data[this.data.length - 1].id + 1;
        } else {
            newId = 1;
        }
        const newEntry = { id: newId, name: entry.name, bday: entry.bday };
        this.data.push(newEntry);
        this.emit('POST', newEntry);
        return newEntry;
    }

    update(id, entry) {
        const index = this.data.findIndex(function (record) {
            return record.id === id; 
        });
        if (index === -1) {
            throw new Error('Запись не найдена');
        }
        this.validateEntry(entry); 
        if (entry.name !== undefined) {
            this.data[index].name = entry.name;
        }
        if (entry.bday !== undefined) {
            this.data[index].bday = entry.bday;
        }
        this.emit('PUT', this.data[index]);
        return this.data[index]; 
    }

    delete(id) {
        const index = this.data.findIndex(function (record) {
            return record.id === id; 
        });
        if (index === -1) {
            throw new Error('Запись не найдена');
        }
        const deletedEntry = this.data.splice(index, 1);
        this.emit('DELETE', deletedEntry[0]);
        return deletedEntry[0];
    }

    commit() {
        console.log('Состояние БД зафиксировано');
        this.emit('COMMIT'); 
    }
}

const DB = new DatabaseCRUD();
module.exports = DB;