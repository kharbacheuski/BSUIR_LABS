package com.api.app.cache;

import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

@Component(value="cache")
@Scope("singleton")
public class NumberCache<T, U> {
    Map<T, U> cache = Collections.synchronizedMap(new HashMap<T, U>());

    public void push(T key, U value) {

        if(!cache.containsKey(key))
            cache.put(key, value);
    }

    public U get(T key) {

        return cache.get(key);
    }
}
