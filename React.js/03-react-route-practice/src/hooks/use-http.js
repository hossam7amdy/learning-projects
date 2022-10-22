import { useCallback, useEffect, useState } from "react";

import { client } from "../utils/axios-utils";

const useHttp = (url) => {
  const [data, setData] = useState();
  const [error, setError] = useState(null);
  const [isLoading, setIsLoading] = useState(false);

  const request = useCallback(async (config) => {
    setIsLoading(true);
    try {
      const { data } = await client(config);
      setData(data);
      return data;
    } catch (err) {
      setError("something went wrong");
    } finally {
      setIsLoading(false);
    }
  }, []);

  useEffect(() => {
    request(url);
  }, [url, request]);

  return {
    data,
    error,
    isLoading,
    request,
  };
};

export default useHttp;
