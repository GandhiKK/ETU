$(() => {
    $(".tabs").tabs({
        classes: {
            "ui-tabs-active": "highlight"
        }
    });

    let socket = io.connect("http://localhost:3030");
    let isEnd = false;

    socket.on('connect', function () {
        socket.json.emit('join', {
            'name': 'ADMIN'
        });
    });

    socket.on('msg', (msg) => {
        appendMessage(msg, 'blue')
    });

    socket.on('start', (msg) => {
        appendMessage(msg, 'red')
    });

    socket.on('price', (msg) => {
        appendMessage(msg, 'green')
    });

    socket.on('END', (msg) => {
        if(!isEnd) {
            isEnd = true;
            appendMessage(msg, "red");
        }
    });

    socket.on('buy', (msg) => {
        let deltaMoney;
        appendMessage(msg);
        for(let element of ($(".partner"))) {
            if(element.firstChild.innerHTML == msg.name) {
                deltaMoney = parseInt(element.lastChild.innerHTML) - parseInt(msg.money);
                element.lastChild.innerHTML = msg.money;
                break;
            }
        }
        let array = msg.art.split("-");
        let author = array[0].substring(0, array[0].length - 1);
        let name = array[1] = array[1].substring(1, array[1].length);
        for(let element of ($(".artInfo"))) {
            if(element.children[0].innerHTML == author && element.children[1].innerHTML == name) {
                element.children[3].innerHTML = msg.name;
                element.children[4].innerHTML = deltaMoney;
                break;
            }
        }
    });
});