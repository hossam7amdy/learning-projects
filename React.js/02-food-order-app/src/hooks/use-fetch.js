import { useEffect, useState } from "react";

const timeout = (seconds) => {
  return new Promise((_, rejecet) => {
    setTimeout(() => {
      rejecet(
        new Error(`Request timeout after ${seconds} seconds. Try again!`)
      );
    }, seconds * 1000);
  });
};

const useFetch = (url = undefined, uploadData = undefined) => {
  const [data, setData] = useState();
  const [error, setError] = useState(null);
  const [isLoading, setIsLoading] = useState(false);

  const fetchAPI = async (url, uploadData = undefined) => {
    setIsLoading(true);
    try {
      const fetchPro = uploadData
        ? fetch(url, {
            method: uploadData.method,
            headers: uploadData.headers,
            body: JSON.stringify(uploadData.body),
          })
        : fetch(url);

      const response = await Promise.race([fetchPro, timeout(5)]);
      if (!response.ok) throw new Error("Something went wrong");
      const responseData = await response.json();

      setData(responseData);
    } catch (err) {
      setError(err.message);
    } finally {
      setIsLoading(false);
    }
  };

  useEffect(() => {
    fetchAPI(url);
  }, [url]);

  return {
    data,
    error,
    isLoading,
    fetchAPI,
  };
};

export default useFetch;
