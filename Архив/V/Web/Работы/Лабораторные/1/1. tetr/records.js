function fillTable() {
    let list = document.getElementById("scores");
    let currTableScores = localStorage["scoreTable"];
    let scores = currTableScores.split(',');

    for (let i = 0; i < 10; i++){
        let score = scores[i].split(' ');
        let scoreNumber = score[score.length-1];
        let playerString = getName(score);
        let newLi = document.createElement('li');
        newLi.innerHTML = playerString + " " + scoreNumber.toString()
        list.appendChild(newLi);
    }
}

function getName(string) {
    let name = "";
    for (let i = 0; i < string.length-1; i++)
        name = name + string[i] + " ";
    return name;
}