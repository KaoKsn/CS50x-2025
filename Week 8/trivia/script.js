document.addEventListener('DOMContentLoaded', function() {
    /* Part 1 */
    let section = document.querySelector('.section');

    section.addEventListener('click', function(event) {
        let choice = event.srcElement.id;

        if (choice == 'choice1') {
            /* Turn the button green */
            section.querySelector('#choice1').style.backgroundColor = 'green';

            /* Display message */
            section.querySelector('#feedback').innerHTML = 'Correct';
        } else {
            /* Turn the button red */
            event.srcElement.style.backgroundColor = 'red';

            /* Display message */
            section.querySelector('#feedback').innerHTML = 'Incorrect';
        }
    });

    /* Part 2 */

    let secondsection = document.querySelector('.secondsection');

    secondsection.querySelector('#confirm').addEventListener('click', function() {

        if (secondsection.querySelector('#answer').value.toLowerCase() == 'russia') {
            secondsection.querySelector('#answer').style.backgroundColor = 'green';
            secondsection.querySelector('#secondfeedback').innerHTML = 'Correct';
        } else {
            secondsection.querySelector('#answer').style.backgroundColor = 'red';
            secondsection.querySelector('#secondfeedback').innerHTML = 'Incorrect';
        }
    });

});
