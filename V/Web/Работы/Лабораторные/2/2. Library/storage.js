//-------------------------------------
//-----Функции работы с сервером-------
//-------------------------------------



const fs = require('fs'); 

//Конструктор Книги
function Book(name, author, release_date, info, id){ 
    this.id = id;
    this.name = name;
    this.author = author;
    this.release_date = release_date;
    this.info = info;
    this.available = true;
    this.return_date = 0;
    //reader_id
    
}

//Конструктор Пользователя
function User(name, id){
    this.id = id;
    this.name = name;
    this.books = [];
}

//Сохранение основного хнанилища
function save_storage(storage){
    fs.writeFile('public/json/storage.json', JSON.stringify(storage), (err) => {
        if (err) throw err;
        console.log('It\'s saved!');
    });

    fs.writeFile('public/json/books.json', JSON.stringify(storage.books), (err) => {
        if (err) throw err;
        console.log('Books saved!');
    });

    fs.writeFile('public/json/users.json', JSON.stringify(storage.users), (err) => {
        if (err) throw err;
        console.log('Users saved!');
    });
}

//Считывание хранилища с файла
function read_storage(){
    let st;
    st = JSON.parse(fs.readFileSync('./public/json/storage.json', 'utf8'));
    return st;
}

//Добавление нового пользователя
function add_user(main_storage, body){
    let new_user = new User(body.name, main_storage.last_user_id++);

    main_storage.users.push(new_user);
    console.log(main_storage);

    save_storage(main_storage);

}

//Добавление новой книги
function add_book(main_storage, {name, author, release_date, info}){
    let new_book = new Book(name, author, release_date, info, main_storage.last_book_id++);
    console.log(new_book);

    main_storage.books.push(new_book);
    console.log(main_storage);

    save_storage(main_storage);
}

//Изменение информации о книге
function change_book(main_storage, {name, author, release_date, info}, id){
    console.log("Before" + JSON.stringify(main_storage));
    main_storage.books.forEach(book => {
        if(book.id == id){
            book.name = name;
            book.author = author;
            book.release_date = release_date;
            book.info = info;
        }
    });
    console.log("After" + JSON.stringify(main_storage));
    save_storage(main_storage);
}

//Выдача книги пользователю
function give_book(main_storage, body, book_id){
    main_storage.books.forEach(book => {
        if(book.id == book_id){
            book.return_date = Date.now() + body.days * 24 * 3600 *1000;
            book.reader_id = body.user_id;
			let user = main_storage.users.find(({id})=>id==body.user_id)
			user && (book.userName=user.name)
			console.log("----------",user)
            book.available = false;

            main_storage.users.find((user) => {  
                return user.id == body.user_id;
            }).books.push(book.id);

        }
    });
    console.log("After" + JSON.stringify(main_storage));
    save_storage(main_storage);
}
 
//Продлить книгу
function extend_book(main_storage, body, id){
    console.log("Before" + JSON.stringify(main_storage));

    main_storage.books.forEach(book => {
        if(book.id == id){
            book.return_date += parseInt(body.extend_days, 10) * 24 * 3600 * 1000;
        }
    });
    save_storage(main_storage);
}

//Вернуть книгу
function return_book(main_storage, book_id){
    main_storage.books.forEach(book => {
        if(book.id == book_id){

            console.log(book.reader_id);
            console.log(book.id);
            let user = main_storage.users.find((user) => {  
                return user.id == book.reader_id;
            });
            console.log(user);
            user.books = user.books.filter((_book_id) => { 
                if(_book_id != book_id) return _book_id;
            });

            console.log(user);
            book.return_date = 0;
            book.reader_id = undefined;
            book.available = true;

            
        }
    });
    console.log("After" + JSON.stringify(main_storage));
    save_storage(main_storage);
}

//Удалить книгу
function delete_book(main_storage, id){
    main_storage.books = main_storage.books.filter((book) => { 
        if(book.id != id) return book;
    });
    console.log("After" + JSON.stringify(main_storage));
    save_storage(main_storage);
}


//Экспорт функций(если этого не сделать, функция не будет видна вне файла)
module.exports = {
    add_user: add_user,
    add_book: add_book,
    change_book: change_book,
    read_storage: read_storage,
    give_book: give_book,
    extend_book: extend_book,
    return_book: return_book,
    delete_book: delete_book,

}
