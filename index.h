const char *INDEX_HTML = R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Dron atmosferyczny</title>
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Open+Sans&family=Poppins:ital,wght@0,500;0,600;0,900;1,300;1,700&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="style.css">

    <style>
      * {
          margin: 0;
          padding: 0;
          font-family: 'Poppins', sans-serif;
      }
      body
      {
          background-color: aliceblue;
      }
      header
      {
          height: auto;
          max-width: 95vw;
          width: 95vw;
          padding: 2vw 2vw 1vw 3vw;
          display: flex;
          flex-wrap: wrap;
          justify-content: space-around;
      }
      header img
      {
          height: auto;
          object-fit: cover;
          max-width: 70%;
          width: 70%;
      }
      header #text
      {
          height: 13vh;
          width: 800px;
          font-size: 3vw;
          text-align: center;
      }
      header text h3
      {
          text-transform: uppercase;
          font-weight: 900;
      }
      #sensor-output
      {
          display: flex;
          overflow: hidden;
          flex-wrap: wrap;
          align-items: center;
          justify-content: center;
          align-items: center;
      }
      .sensor-data
      {
          border: 3px solid black;
          border-radius: 100px;
          background-color: #bbccFF;
          min-width: 250px;
          min-height: 350px;
          width: 15vw;
          margin: 15px;
          align-items: center;
          justify-content: center;
          text-align: center;
          position: relative;
          display: flex;
      }

      .sensor-data-name
      {
          position: absolute;
          top: 0;
          left: 0;
          padding: 20px;
          font-size: 18px;
          background-color: #5F9ae0;
          border-radius: 20vw;
      }
      .sensor-data-value
      {
          padding: 3vw;
          font-size: 60px;
          align-items: center;
      }
      .sensor-data-name
      {
          position: absolute;
          top: 0;
          left: 0;
      }
      footer
      {
          width: 100vw;
          padding: 3px;
          background-color: #000;
          text-align: center;
          color: #fff;
          position: fixed;
          bottom: 0;
      }
    </style>
</head>
<body>
    <header>
        <img src="img/cropped-robo-logo-2.png" alt="Robonomik">
        <div id="text"><h3>Dron atmosferyczny</h3></div>
    </header>
    <article>
        <!-- .sensor-data#s*6>.sensor-data-name+.sensor-data-value -->
        <div id="sensor-output">
          <div class="sensor-data" id="s">
              <div class="sensor-data-name">PM 1.0</div>
              <div class="sensor-data-value" id="pm_1_0">0</div>
          </div>
          <div class="sensor-data" id="s">
              <div class="sensor-data-name">PM 2.5</div>
              <div class="sensor-data-value" id="pm_2_5">0</div>
          </div>
          <div class="sensor-data" id="s">
              <div class="sensor-data-name">PM 10</div>
              <div class="sensor-data-value" id="pm_10">0</div>
          </div>
          <div class="sensor-data" id="s">
              <div class="sensor-data-name">Temperatura</div>
              <div class="sensor-data-value" id="temperature">0</div>
          </div>
          <div class="sensor-data" id="s">
              <div class="sensor-data-name">Wilgotność</div>
              <div class="sensor-data-value" id="humidity">0</div>
          </div>
          <div class="sensor-data" id="s">
              <div class="sensor-data-name">Ciśnienie</div>
              <div class="sensor-data-value" id="pressure">0</div>
          </div>
        </div>
    </article>
    <footer>
        <p>Autor: Radosław Berdzik &copy; 2023 Robonomik. Wszelkie prawa zastrzeżone.</p>
    </footer>
    <script>
      let pm_1_0 = document.getElementById('pm_1_0');
      let pm_2_5 = document.getElementById('pm_2_5');
      let pm_10 = document.getElementById('pm_10');
      let temperature = document.getElementById('temperature');
      let humidity = document.getElementById('humidity');
      let pressure = document.getElementById('pressure');

      function getJson(){
          fetch("http://192.168.4.1/api")
              .then(response => response.json())
              .then(json => {
                  
                  let sensor_data = {};
                  sensor_data = json;

                  console.log(sensor_data);

                  pm_1_0.innerHTML = sensor_data.pm_1_0;
                  pm_2_5.innerHTML = sensor_data.pm_2_5;
                  pm_10.innerHTML = sensor_data.pm_10;
                  temperature.innerHTML = sensor_data.temperature;
                  humidity.innerHTML = sensor_data.humidity;
                  pressure.innerHTML = Math.round(sensor_data.pressure);

              }
          );
      };

      setInterval(getJson, 500);
    </script>
</body>
</html>
)";
