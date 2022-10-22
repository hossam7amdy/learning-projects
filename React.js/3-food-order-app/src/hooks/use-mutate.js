import axois from "axios";
import { useState, useCallback } from "react";

const useMutate = () => {
  const [error, setError] = useState(null);
  const [isLoading, setIsLoading] = useState(false);

  const request = useCallback(async (config) => {
    setError(null);
    setIsLoading(true);

    try {
      const response = await axois(config);
      return response;
    } catch (err) {
      setError(err.message);
      throw new Error(err.message || "something went wrong");
    } finally {
      setIsLoading(false);
    }
  }, []);

  return {
    error,
    request,
    isLoading,
  };
};

export default useMutate;
