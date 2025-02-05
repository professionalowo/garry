console.log('Hello from script.js');

const esp = document.getElementById('ip').value
const buttons = document.querySelectorAll('button')
buttons.forEach(button => {
    button.addEventListener('click',async () => {
        await fetch(`http://${esp}/${button.id}`)
    })
});