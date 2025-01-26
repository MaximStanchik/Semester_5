import { createClient } from 'webdav';
import fs from 'fs';
import path from 'path';

const url = 'https://webdav.yandex.ru';
const username = 'heavenGII'; 
const password = 'hywrnqeymtpwmqin'; 

console.log(`Username: ${username}, Password: ${password}`); 
const client = createClient(url, {
    username,
    password
});

async function createFolder(folderName) {
    await client.createDirectory(folderName);
    console.log(`Папка "${folderName}" создана.`);
}

async function uploadFile(localFilePath, remoteFilePath) {
    if (!fs.existsSync(localFilePath)) {
        console.error(`Файл "${localFilePath}" не найден.`);
        return;
    }
    await client.putFileContents(remoteFilePath, fs.readFileSync(localFilePath));
    console.log(`Файл "${localFilePath}" загружен как "${remoteFilePath}".`);
}

async function downloadFile(remoteFilePath, localFilePath) {
    const data = await client.getFileContents(remoteFilePath);
    fs.writeFileSync(localFilePath, data);
    console.log(`Файл "${remoteFilePath}" загружен в "${localFilePath}".`);
}

async function copyFile(sourcePath, destinationPath) {
    await client.copyFile(sourcePath, destinationPath);
    console.log(`Файл "${sourcePath}" скопирован в "${destinationPath}".`);
}

async function deleteFile(filePath) {
    await client.deleteFile(filePath);
    console.log(`Файл "${filePath}" удален.`);
}

async function deleteFolder(folderPath) {
    const files = await client.getDirectoryContents(folderPath);
    for (const file of files) {
        await client.deleteFile(file.filename);
    }
    await client.deleteFile(folderPath); 
    console.log(`Папка "${folderPath}" удалена.`);
}

(async () => {
    try {
        await createFolder('test-folder');
        await uploadFile(path.join(process.cwd(), 'local-file.txt'), 'test-folder/remote-file.txt');
        await downloadFile('test-folder/remote-file.txt', 'downloaded-file.txt');
        await copyFile('test-folder/remote-file.txt', 'test-folder/remote-file-copy.txt');
        await deleteFile('test-folder/remote-file-copy.txt');
        await deleteFolder('test-folder');
    } catch (error) {
        console.error(error);
    }
})();