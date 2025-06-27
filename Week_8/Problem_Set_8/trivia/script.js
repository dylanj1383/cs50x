document.addEventListener('DOMContentLoaded', function() {
    const correctAnswer = "De Broglie";
    const buttons = document.querySelectorAll('button');
    const feedback = document.querySelector('#q1_result');

    buttons.forEach(function(button) {
        button.addEventListener('click', function(event) {
            // Reset all buttons
            buttons.forEach(btn => {
                btn.style.backgroundColor = '';
                btn.style.color = '';
            });

            // Apply color to clicked button
            if (button.innerText.trim() === correctAnswer) {
                button.style.backgroundColor = 'green';
                button.style.color = 'white';
                feedback.innerHTML = 'Correct!'

            } else {
                button.style.backgroundColor = 'red';
                button.style.color = 'white';
                feedback.innerHTML = 'Incorrect.'
            }
        });
    });
});


document.querySelector('form').addEventListener('submit', function (event){
    const feedback = document.querySelector('#q2_result');
    const text = document.querySelector("#mathematician");

    const answer = text.value.trim().toLowerCase();

    if (answer === "euler" || answer === "leonhard euler"){
        feedback.innerHTML = 'Correct!';
        text.style.color = 'green';
    }
    else{
        feedback.innerHTML = 'Incorrect.';
        text.style.color = 'red';
    }
    event.preventDefault(); 
});


document.querySelector('form').addEventListener('keydown', function (event){
    const text = document.querySelector("#mathematician");
    text.style.color = '';

});