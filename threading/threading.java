public class threading {

    public static void main(String[] args) {
        Thread theThread = new fileThread();

        Runnable theRunnable = new fileRunnable();
        Thread runnableThread = new Thread(theRunnable);

        theThread.start();
        runnableThread.start();

        System.out.println("Hello, World!");
    }
}

class fileThread extends Thread {
    public void run() {
        for (int i = 0; i < 100; i++){
            System.out.println("Class running");
        }
    }
}

class fileRunnable implements Runnable {
    public void run() {
        for (int i = 0; i < 100; i++){
            System.out.println("Interface running");
        }
    }
}