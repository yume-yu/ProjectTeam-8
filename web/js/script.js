document.addEventListener("DOMContentLoaded",function(){
	document.getElementById("enter_button").addEventListener('click',function(){
		var elm = document.getElementsByClassName("animation");
		anime({
			targets: elm,
			duration: 3000,
			opacity: 0,
			height: 0,
			complate:function(){
				elem.style.display="none";
				elem.style.height="0px";
			}
		})
		document.querySelector('body').className = "canScroll";
		document.querySelector('html').className = "canScroll";
	})
})
