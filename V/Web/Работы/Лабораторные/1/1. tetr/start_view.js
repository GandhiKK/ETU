function saveName() {
    const inpElement = document.getElementsByName("playerName")[0];
    if (inpElement.value === "")
    {
        alert('Нет имени')
        return}
    else store(inpElement)
}

function store(source) {
    localStorage["tetris.username"] = source.value;
    redirectToGame()
}

function redirectToGame() {
    window.location = "main.html";
}