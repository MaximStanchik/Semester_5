const myPromise = new Promise (function(resolve, reject) {
    const errorOccured = true;
    if (errorOccured) {
        reject(new Error ("Что-то пошло не так!"));
    }
    else {
        resolve("Промис успешно разрешен");
    }
});

myPromise
    .then(function(rusult) {
        console.log("result");
    })
    .catch(function (error) {
        console.log("Ошибка: ", error.message);
    });