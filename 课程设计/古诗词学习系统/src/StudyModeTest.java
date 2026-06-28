public class StudyModeTest {
    public static void main(String[] args) {
        System.out.println("开始测试学习模式功能...");
        
        // 创建并初始化系统
        PoemSystem system = new PoemSystem();
        int poemCount = system.loadPoemsFromFile("d:\\古诗学习系统\\poems.txt");
        
        if (poemCount > 0) {
            System.out.println("\n系统初始化成功，现在进入学习模式测试...");
            System.out.println("（请在交互界面中测试各项功能）");
            
            // 创建并启动学习模式
            StudyMode studyMode = new StudyMode(system);
            studyMode.start();
            studyMode.close();
            
            // 显示测试后的学习记录
            System.out.println("\n测试结束后的学习记录：");
            System.out.println(system.getStudyRecord());
        } else {
            System.out.println("系统初始化失败，无法进入学习模式！");
        }
    }
}