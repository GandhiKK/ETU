let beginTimeMarket;

/**
 * Отправить сообщение в информационный чат
 *
 * @param socketMessage
 * @param color
 */

function appendMessage(socketMessage, color = 'black') {
    new Promise((resolve, reject) => {
        console.log(`${new Date().toLocaleTimeString()}: ${color} ${socketMessage.message} ${socketMessage.time}`);
    }).then();

    let div = document.createElement("div");
    div.style.color = color;
    div.innerHTML = `<span class="info-message__time">${new Date(socketMessage.time).toLocaleTimeString()}</span> ${socketMessage.message}`;
    $('#info-messages .content').append(div);
}
