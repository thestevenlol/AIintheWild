import http.server
import ssl

server_address = ('localhost', 4443)  # Port 4443 is used for HTTPS
httpd = http.server.HTTPServer(server_address, http.server.SimpleHTTPRequestHandler)

# Wrap the socket with SSL
httpd.socket = ssl.wrap_socket(httpd.socket,
                               certfile='./localhost.pem',
                               keyfile='./localhost-key.pem',
                               server_side=True)

print("Serving on https://localhost:4443")
httpd.serve_forever()
