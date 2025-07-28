// Incrementing scores
document.addEventListener('DOMContentLoaded', function() {
    body = document.querySelector('body');
    table = document.querySelector('table');

    // Dark mode.
    body.querySelector('#darkmode').addEventListener('click', function() {
        body.style.backgroundColor = 'black';
        body.style.color = 'white';
    });

    // Score Increments.
    let score1 = 0,
        score2 = 0;

    table.querySelector('#scr1').innerHTML = 0;
    table.querySelector('#scr2').innerHTML = 0;

    table.querySelector('#incr1').addEventListener('click', function() {
        score1++;

        if (score1 == 5) {
            let winner = 1;
            document.querySelector('#winner').innerHTML = `Team ${winner} won!`;
            score1 = 0;
            score2 = 0;
            table.querySelector('#scr1').innerHTML = score1;
            table.querySelector('#scr2').innerHTML = score2;
            body.style.backgroundColor = 'white';
            body.style.color = 'black';
        }
        else {
            document.querySelector('#winner').innerHTML = '';
            table.querySelector('#scr1').innerHTML = score1;
            body.style.backgroundColor = 'red';
        }
    });

    table.querySelector('#incr2').addEventListener('click', function() {
        score2++;

        if (score2 == 5) {
            let winner = 2;
            document.querySelector('#winner').innerHTML = `Team ${winner} won!`;
            score1 = 0
            score2 = 0;
            table.querySelector('#scr1').innerHTML = score1;
            table.querySelector('#scr2').innerHTML = score2;
            body.style.backgroundColor = 'white';
            body.style.color = 'black';
        }
        else {
            document.querySelector('#winner').innerHTML = '';
            table.querySelector('#scr2').innerHTML = `${score2}`;
            body.style.backgroundColor = 'blue';
        }
    });

});
