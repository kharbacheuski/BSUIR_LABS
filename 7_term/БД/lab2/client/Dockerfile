FROM node:19.6.0-alpine as build

ARG BASE_API_URL
ENV REACT_APP_BASE_API_URL=$BASE_API_URL

WORKDIR /usr/app
COPY . /usr/app
RUN npm i
RUN npm run build

FROM nginx:1.23.1-alpine
COPY ./nginx.conf /etc/nginx/nginx.conf
RUN rm -rf /usr/share/nginx/html/*

COPY --from=build /usr/app/public /usr/share/nginx/html
CMD ["nginx", "-g", "daemon off;"]