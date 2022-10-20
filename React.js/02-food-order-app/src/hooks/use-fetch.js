import axois from "axios";
import { useEffect, useState } from "react";

const useFetch = (config) => {
  const [data, setData] = useState();
  const [error, setError] = useState(null);
  const [isLoading, setIsLoading] = useState(false);

  useEffect(() => {
    const request = async () => {
      setIsLoading(true);
      try {
        const { data } = await axois(config);
        setData(data);
      } catch (err) {
        setError(err.message);
      } finally {
        setIsLoading(false);
      }
    };

    request();
  }, [config]);

  return {
    data,
    error,
    isLoading,
  };
};

export default useFetch;
