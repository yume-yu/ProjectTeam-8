document.querySelector('.animation').addEventListener('click',function(){
	document.querySelector('.animation').classList.add('started');
	document.getElementsByTagName('body')[0].classList.toggle('canScroll');
	document.getElementsByTagName('html')[0].classList.toggle('canScroll');
})

function switchExp(label){
	document.getElementById(label).classList.toggle('selected');
}

document.getElementById('Character').getElementsByTagName('button')[0].addEventListener('click',function(){
	document.getElementById('Character').getElementsByClassName('selected')[1].classList.toggle('selected');
	event.target.classList.add('selected');
	for(var i = 0; i < document.getElementById('Character').getElementsByTagName('div').length; i++){
		document.getElementById('Character').getElementsByTagName('div')[i].classList.remove('selected');
	}
	switchExp('arist_exp');
})
document.getElementById('Character').getElementsByTagName('button')[1].addEventListener('click',function(){
	document.getElementById('Character').getElementsByClassName('selected')[1].classList.toggle('selected');
	//document.getElementById('Character').querySelector('.selected').classList.toggle('selected');
	event.target.classList.add('selected');
	for(var i = 0; i < document.getElementById('Character').getElementsByTagName('div').length; i++){
		document.getElementById('Character').getElementsByTagName('div')[i].classList.remove('selected');
	}
	switchExp('naoki_exp');
})
document.getElementById('Character').getElementsByTagName('button')[2].addEventListener('click',function(){
	document.getElementById('Character').getElementsByClassName('selected')[1].classList.toggle('selected');
	//document.getElementById('Character').querySelector('.selected').classList.toggle('selected');
	event.target.classList.add('selected');
	for(var i = 0; i < document.getElementById('Character').getElementsByTagName('div').length; i++){
		document.getElementById('Character').getElementsByTagName('div')[i].classList.remove('selected');
	}
	switchExp('lirel_exp');
})

window.addEventListener('load', function(){
	window.scroll(top);
	/* $B%?%$%H%k%"%K%a!<%7%g%s=hM}(B */
	//var title_logo = document.querySelector('#title_menu h1');
	//var title_logo = document.getElementById('title_menu').querySelector('.ready');;
	var title_logo = document.getElementsByClassName('ready');
	var enter_button = document.getElementsByTagName('button');

	for(var i = 0; i < title_logo.length; i++){
		title_logo[i].classList.toggle("loaded");
	}
})

