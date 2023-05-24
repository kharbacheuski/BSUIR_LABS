package com.api.app;

import com.api.app.models.ErrorModel;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;
import org.springframework.web.server.ResponseStatusException;

@RestControllerAdvice
public class ExceptionHandlerController {

    private static final Logger logger = LoggerFactory.getLogger(NumberController.class);

    @ExceptionHandler({ ResponseStatusException.class })
    public ResponseEntity<Object> handleException(ResponseStatusException ex) {
        var errorModel = new ErrorModel();
        errorModel.ErrorMessage = ex.getReason();

        logger.info("Exception: " + ex.getMessage());

        return new ResponseEntity<>(errorModel, ex.getStatus());
    }
}
