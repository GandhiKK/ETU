$(document).ready(()=> {
    start_config();
});

function start_config() {
    $('#main').prop("disabled", false);
    $('#cards').prop("disabled", true);
    $('#setting').prop("disabled", false);
    $('#id02').removeAttr("style").hide();
    $('#id01').removeAttr("style").hide();
}

function edit_person(name, money, id) {
    $('#id02').show();
    $('input[name="name"]').val(name);
    $('input[name="money"]').val(money);
    $('form[name="pForm"]').attr('action', 'editPerson/'+id);
}

function new_person() {
    $('#id01').show();
}
