import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

public class Client {
    private static final String END = "END";

    public static void main(String[] args) {
        String host = "127.0.0.1";
        int port = 8084;

        try {
            Socket socket = new Socket(host, port);
            System.out.println("Connected to " + host + ":" + port);

            BufferedReader inputReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter outputWriter = new PrintWriter(socket.getOutputStream(), true);

            BufferedReader consoleReader = new BufferedReader(new InputStreamReader(System.in));

            System.out.print("Type your username: ");
            String username = consoleReader.readLine();

            String msg = "OK";
            System.out.println("Send the message " + END + " to finish");

            while (!msg.equals(END)) {
                System.out.print("Write a message and press Enter to send it:\n");
                msg = consoleReader.readLine();
                outputWriter.println("[" + username + "]: " + msg);

                String response = inputReader.readLine();
                System.out.println(response);
            }

            socket.close();
            System.out.println("Connection closed");
        } catch (UnknownHostException e) {
            System.err.println("Unknown host: " + host);
            e.printStackTrace();
        } catch (IOException e) {
            System.err.println("Error connecting to server: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
