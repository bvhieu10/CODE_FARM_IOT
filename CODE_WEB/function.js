// khoi tao cac thong so
let btn1 = document.querySelector('#btn1');
let img1 = document.querySelector('#den');
let btn2 = document.querySelector('#btn2');
// functions nut bam
// const database=firebase.database();
// const deviceRef=database.ref('quan1');

btn1.addEventListener('click', ()=>{
    img1.src = 'image/lamp_on.png'; 
    firebase.database().ref("thietbi1").set({den: 1})
})
btn2.addEventListener('click', ()=>{
    img1.src = 'image/lamp_off.png';
    firebase.database().ref("thietbi1").set({den: 0})
})


// khoi tao cac thong so
let btn3 = document.querySelector('#btn3');
let img2 = document.querySelector('#dieuhoa');
let btn4 = document.querySelector('#btn4');
// functions nut bam
btn3.addEventListener('click', ()=>{
    img2.src = 'image/air_condition_on.png'; 
    firebase.database().ref("thietbi2").set({dieuhoa:1})
})

btn4.addEventListener('click', ()=>{
    img2.src = 'image/air_condition_off.png';
    firebase.database().ref("thietbi2").set({dieuhoa:0})
})



// khoi tao cac thong s
let btn5 = document.querySelector('#btn5');
let img3 = document.querySelector('#giamsat');
let btn6 = document.querySelector('#btn6');

// functions nut bam
btn5.addEventListener('click', ()=>{
     img3.src = 'image/cam_on.png' ;
     firebase.database().ref("thietbi3").set({giamsat:1})

})
btn6.addEventListener('click', ()=>{
    img3.src = 'image/cam_off.png';
    firebase.database().ref("thietbi3").set({giamsat: 0})

})

// your_script.js

document.addEventListener('DOMContentLoaded', function () {
    // ThingSpeak API key và channel ID của bạn
    const apiKey = 'HFPE539JB2D66VRE';
    const channelId = '2176099';

        // Tham chiếu đến Firebase Realtime Database
        const database = firebase.database();
        const nhietDoRef = database.ref('Nhiet do');
        // Lắng nghe sự kiện khi có thay đổi trong Firebase
        nhietDoRef.on('value', function (snapshot) {
            const nhietDoValue = snapshot.val();
            // Gửi dữ liệu nhiệt độ lên ThingSpeak thông qua API
            $.ajax({
                type: 'POST',
                url: `https://api.thingspeak.com/update?api_key=${apiKey}&field1=${nhietDoValue}`,
            });
        });
    });

document.addEventListener('DOMContentLoaded', function () {
    // ThingSpeak API key và channel ID của bạn
    const apiKey = 'HFPE539JB2D66VRE';
    const channelId = '2176099';

        // Tham chiếu đến Firebase Realtime Database
        const database = firebase.database();
        const doAmRef = database.ref('Do am');
        // Lắng nghe sự kiện khi có thay đổi trong Firebase
        doAmRef.on('value', function (snapshot) {
            const doAmRef = snapshot.val();
            $.ajax({
                type: 'POST',
                url: `https://api.thingspeak.com/update?api_key=${apiKey}&field2=${doAmRef}`,
            });
        });
    });

document.addEventListener('DOMContentLoaded', function () {
    // ThingSpeak API key và channel ID của bạn
    const apiKey = 'HFPE539JB2D66VRE';
    const channelId = '2176099';

        // Tham chiếu đến Firebase Realtime Database
        const database = firebase.database();
        const khongKhiRef = database.ref('Khong khi');
        // Lắng nghe sự kiện khi có thay đổi trong Firebase
        khongKhiRef.on('value', function (snapshot) {
            const khongKhiRef = snapshot.val();
            $.ajax({
                type: 'POST',
                url: `https://api.thingspeak.com/update?api_key=${apiKey}&field3=${khongKhiRef}`,
            });
        });
    });