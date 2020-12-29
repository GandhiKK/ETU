//-------------------------------------
//-------------AJAX запросы------------
//-------------------------------------


//Сортировка по дате возвращения и вывод на экран книг, хранящихся у пользователя
function sort_date() {
    var xhr = new XMLHttpRequest();

    xhr.open('GET', '../json/books.json', false); //считаный файл записывается в xhr.responseText как строка
    xhr.onload = () => {
        //преобразуем строку в объект
        let books = JSON.parse(xhr.responseText);

        books.sort((book_a, book_b) => {
            return book_b.return_date - book_a.return_date;
        })

        books = books.filter((book) => {
            return book.available === false;
        })
        renderHTML(books);
    }
    xhr.send();

    if (xhr.status != 200) {
        alert('Ошибка ' + xhr.status + ': ' + xhr.statusText);
    }
}

//Вывод на экран доступных книг(В наличии)
function sort_available() {
    var xhr = new XMLHttpRequest();

    xhr.open('GET', '../json/books.json', false);
    xhr.onload = () => {
        let books = JSON.parse(xhr.responseText);

        books = books.filter((book) => {
            return book.available === true;
        })

        renderHTML(books);
    }
    xhr.send();

    if (xhr.status != 200) {
        alert('Ошибка ' + xhr.status + ': ' + xhr.statusText);
    }
}

function print_all() {
    var xhr = new XMLHttpRequest();

    xhr.open('GET', '../json/books.json', false);
    xhr.onload = () => {
        let books = JSON.parse(xhr.responseText);
        renderHTML(books);
    }
    xhr.send();

    if (xhr.status != 200) {
        alert('Ошибка ' + xhr.status + ': ' + xhr.statusText);
    }

}

showAddedUserAlert = function () {
    if((document.getElementsByName("name")[0]).value !== "") alert("Пользователь успешно добавлен!");
}
// выюирает книги по категрори и формирует на основвиии аякс запрос и выплевыает их
function renderHTML(books) {
    let htmlString = "";
    for (i = 0; i < books.length; i++) {
        let date = new Date(books[i].return_date);
        let cur_date = new Date();
        let over = (cur_date > date) ? true : false;

        htmlString +=
            `<div style="border: 1px solid black">
            <a href="/book_card/${books[i].id}">${books[i].name}</a>
            `;
        if (over && !books[i].available){
            htmlString +=
                `<p><b><span style="color: red">Просрочено</span></b></p>
                `;
        }
        if (books[i].available) {
            htmlString +=
                `<p><b><span style="color: green">В наличии</span></b></p>
                `;
        } else {
            htmlString +=
                `<p>У читателя до ${date.toDateString()}</p>
            `;
        }

        htmlString +=
            `<form method="GET" action="/${books[i].id}">
            <button type="submit">Удалить</button>
        </form></div>
        `
    }

    console.log(htmlString);
    document.getElementById("book_list").innerHTML = htmlString;

}


//Вывод инвормации о пользователе, при нажатии на его ID(на странице книги, когда она читается)
function user(id) {
    var xhr = new XMLHttpRequest();
    let user;

    xhr.open('GET', '../json/users.json', false);
    console.log(xhr);
    xhr.onload = () => {
        console.log(xhr.responseText);

        let users = JSON.parse(xhr.responseText);
        console.log(id);

        user = users.find((_user) => {
            console.log(_user.id);
            return _user.id == id;
        })
    }
    xhr.send();

    if (xhr.status != 200) {
        alert('Ошибка ' + xhr.status + ': ' + xhr.statusText);
    } else {
        alert(`
        ID: ${user.id}
        Имя пользователя: ${user.name}
        Читаемые книги: ${user.books}`);
    }
}

function isValidate(input){
    let now = new Date();
    if (input.value < 0 || input.value > now.getFullYear()) {
        input.setCustomValidity("Введите корректный год выпуска книги");
    }
    else {
        input.setCustomValidity("");
    }
}