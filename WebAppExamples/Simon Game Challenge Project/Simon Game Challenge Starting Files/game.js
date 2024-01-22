
var userClickedPattern = [];
var gamePattern = [];
var buttonColours = ["red", "blue", "green", "yellow"];
var started = false;
var wrongAudio = new Audio("sounds/wrong.mp3");
let level = 0;


$(document).keypress(function() {
    if(started == false)
    {
        started = true;
        $("#level-title").text("Level " + level);
        nextSequence();
    }
});

$(".btn").click(function() {
    var userChosenColour = $(this).attr("id");
    userClickedPattern.push(userChosenColour);
    console.log(userClickedPattern);

    //$("#" + userChosenColour).fadeOut(100).fadeIn(100).fadeOut(100).fadeIn(1000);
    playSound(userChosenColour);
    animatePress(userChosenColour);
    checkAnswer(userClickedPattern.length-1);
})

function nextSequence()
{
    level++;
    $("#level-title").text("Level " + level);
    let randomNumber = Math.floor(Math.random() * 4);
    var randomChosenColour = buttonColours[randomNumber];
    gamePattern.push(randomChosenColour);
    $("#" + randomChosenColour).fadeOut(100).fadeIn(100).fadeOut(100).fadeIn(1000);
    playSound(randomChosenColour);

}

function playSound(name) {
    var audio = new Audio("sounds/" + name + ".mp3");
    audio.play();
}

function animatePress(currentColor){
    $("#" + currentColor).addClass("pressed");
    setTimeout(function(){
        $("#" + currentColor).removeClass("pressed");
    }, 100);
}

function checkAnswer(index) {
    if(userClickedPattern[index] === gamePattern[index])
    {
        console.log("success");
        if(userClickedPattern.length == gamePattern.length)
        {
            setTimeout(function() {
                nextSequence();
            }, 1000);
            userClickedPattern = []; // reset user click pattern
        }
    }
    else
    {
        console.log("wrong");
        wrongAudio.play();
        $("body").addClass("game-over");
        setTimeout(function(){
            $("body").removeClass("game-over");
        }, 200);
        startOver();
        $("#level-title").text("Game Over, Press Any Key to Restart");
        
    }
}

function startOver() {
    started = false;
    gamePattern = []; // reset game pattern
    userClickedPattern = []; // reset user click pattern
    level = 0; // reset level 
}