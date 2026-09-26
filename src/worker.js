export default {
  async fetch(request) {
    const CNN_URL =
      "https://production.dataviz.cnn.io/index/fearandgreed/graphdata";

    try {
      const response = await fetch(CNN_URL, {
        method: "GET",
        headers: {
          "User-Agent":
            "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 Chrome/131.0.0.0 Safari/537.36",
          "Accept":
            "application/json, text/plain, */*",
          "Accept-Language":
            "en-US,en;q=0.9",
          "Referer":
            "https://www.cnn.com/",
          "Origin":
            "https://www.cnn.com"
        }
      });

      if (!response.ok) {
        return new Response(
          JSON.stringify({
            error: "CNN request failed",
            status: response.status
          }),
          {
            status: 502,
            headers: {
              "Content-Type": "application/json",
              "Access-Control-Allow-Origin": "*"
            }
          }
        );
      }

      const data = await response.json();

      const score = data.fear_and_greed?.score;
      const rating = data.fear_and_greed?.rating;

      if (score === undefined || rating === undefined) {
        return new Response(
          JSON.stringify({
            error: "CNN data format unexpected"
          }),
          {
            status: 502,
            headers: {
              "Content-Type": "application/json",
              "Access-Control-Allow-Origin": "*"
            }
          }
        );
      }

      // Only send the information your ESP32 actually needs
      const result = {
        score: Math.round(score),
        rating: rating
      };

      return new Response(JSON.stringify(result), {
        headers: {
          "Content-Type": "application/json",
          "Access-Control-Allow-Origin": "*",
          "Cache-Control": "public, max-age=900"
        }
      });

    } catch (error) {
      return new Response(
        JSON.stringify({
          error: error.message
        }),
        {
          status: 500,
          headers: {
            "Content-Type": "application/json",
            "Access-Control-Allow-Origin": "*"
          }
        }
      );
    }
  }
};
