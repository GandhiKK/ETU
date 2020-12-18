//--------------------------------------------
//--------Обработка нажатий на кнопки---------
//--------------------------------------------



document.getElementById("change_btn").addEventListener("click", () => {
    document.getElementById("book_change").style.visibility = "visible";
    document.getElementById("book_change").style.height = "auto";
});
if(document.getElementById("give_btn")){
    document.getElementById("give_btn").addEventListener("click", () => {
        document.getElementById("book_give").style.visibility = "visible";
        document.getElementById("book_give").style.height = "auto";
    });
}else {
    document.getElementById("extend_btn").addEventListener("click", () => {
        document.getElementById("book_extend").style.visibility = "visible";
        document.getElementById("book_extend").style.height = "22px";

    });

}
