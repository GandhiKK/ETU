$(document).ready(()=> {
    start_config();
});

function start_config() {
    $('#main').prop("disabled", true);
    $('#cards').prop("disabled", false);
    $('#setting').prop("disabled", false);
    $('#id02').removeAttr("style").hide();
    $('#id01').removeAttr("style").hide();
}

function edit_picture(name, artist, price, min, max, id) {
    $('#id01').removeAttr("style").hide();
    $('#id02').show();
    $('input[name="name"]').val(name);
    $('input[name="artist"]').val(artist);
    $('input[name="price"]').val(price);
    $('input[name="min"]').val(min);
    $('input[name="max"]').val(max);
    $('form[name="postForm"]').attr('action', 'editPicture/'+id);
}

function new_picture() {
    let data = new FormData();
    data.append('name', $('name').value)
    data.append('artist', $('artist').value)
    data.append('price', $('price').value)
    data.append('min', $('min').value)
    data.append('max', $('max').value)
    data.append('pt', $('pt').value)

  /*  let xhr = new XMLHttpRequest()
    xhr.open("POST", "newPicture/")
    xhr.send(data) */
}