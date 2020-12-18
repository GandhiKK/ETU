$(() => {
    $("#enter").on("click", () => {
        window.location = `logon/${$("input").val()}`;
    });

    $("body").keypress((event) => {
        if(event.key === "Enter") window.location = `logon/${$("input").val()}`;
    });

    $("input").focus();
});