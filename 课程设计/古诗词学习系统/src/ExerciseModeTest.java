import java.util.*;

public class ExerciseModeTest {
    public static void main(String[] args) {
        // 初始化古诗学习系统
        PoemSystem system = new PoemSystem();
        
        // 加载古诗数据
        System.out.println("正在加载古诗数据...");
        String filePath = "d:\\古诗学习系统\\poems.txt";
        int poemCount = system.loadPoemsFromFile(filePath);
        
        if (poemCount == 0) {
            System.out.println("无法加载古诗数据，测试无法继续！");
            return;
        }
        
        System.out.println("成功加载 " + poemCount + " 首古诗！\n");
        
        // 为了测试练习模式，我们需要预先添加一些古诗到已掌握列表
        System.out.println("正在添加一些古诗到已掌握列表以便测试练习模式...");
        
        // 添加一些古诗到已掌握列表（选择至少4句的古诗用于诗句填空测试）
        int addedCount = 0;
        for (Poem poem : system.getAllPoems()) {
            // 选择至少4句的古诗
            if (poem.getLines().size() >= 4 && addedCount < 5) {
                system.addToMasteredPoems(poem);
                System.out.println("添加已掌握：《" + poem.getTitle() + "》 - " + poem.getPoet().getName());
                addedCount++;
            }
        }
        
        System.out.println("\n已成功添加 " + system.getMasteredPoems().size() + " 首古诗到已掌握列表！");
        
        // 启动练习模式测试
        System.out.println("\n===== 开始测试练习模式 =====");
        System.out.println("提示：在测试过程中，您可以：");
        System.out.println("1. 尝试古诗标题诗人练习");
        System.out.println("2. 尝试诗句填空练习");
        System.out.println("3. 查看练习历史记录");
        System.out.println("0. 退出练习模式");
        System.out.println("\n请记住已添加的古诗信息，以便测试练习模式：");
        
        // 显示已添加的古诗信息供用户参考
        for (Poem poem : system.getMasteredPoems()) {
            System.out.println("《" + poem.getTitle() + "》 - " + poem.getPoet().getName());
            System.out.println("诗句：");
            for (int i = 0; i < poem.getLines().size(); i++) {
                System.out.println((i + 1) + ". " + poem.getLines().get(i));
            }
            System.out.println();
        }
        
        // 创建并启动练习模式
        ExerciseMode exerciseMode = new ExerciseMode(system);
        exerciseMode.start();
        exerciseMode.close();
        
        // 测试结束后显示学习记录
        System.out.println("\n===== 测试结束 =====");
        System.out.println("\n当前学习记录信息：");
        System.out.println("已掌握古诗数量：" + system.getMasteredPoems().size());
        System.out.println("练习次数：" + system.getStudyRecord().getExerciseResults().size());
        
        // 显示最近的练习记录
        if (!system.getStudyRecord().getExerciseResults().isEmpty()) {
            System.out.println("\n最近的练习记录：");
            List<ExerciseResult> recentResults = system.getStudyRecord().getRecentExerciseResults(5);
            for (int i = 0; i < recentResults.size(); i++) {
                ExerciseResult result = recentResults.get(i);
                System.out.println((i + 1) + ". " + result);
            }
        }
        
        System.out.println("\n练习模式测试完成！");
    }
}