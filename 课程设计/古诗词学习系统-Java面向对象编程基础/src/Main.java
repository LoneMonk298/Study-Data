import java.util.*;

public class Main {
    private static final String POEM_FILE_PATH = "d:\\古诗学习系统\\poems.txt";
    private static final String RECORD_FILE_PATH = "d:\\古诗学习系统\\study_record.dat";
    
    public static void main(String[] args) {
        // 初始化系统
        PoemSystem system = new PoemSystem();
        
        // 显示欢迎信息
        showWelcomeMessage();
        
        try {
            // 加载古诗数据
            System.out.println("正在加载古诗数据...");
            int poemCount = system.loadPoemsFromFile(POEM_FILE_PATH);
            
            if (poemCount == 0) {
                System.out.println("警告：无法加载古诗数据！系统可能无法正常运行。");
            } else {
                System.out.println("成功加载 " + poemCount + " 首古诗！");
            }
            
            // 尝试加载学习记录
            System.out.println("正在加载学习记录...");
            boolean recordLoaded = system.loadStudyRecord();
            
            if (recordLoaded) {
                System.out.println("成功加载学习记录！");
                System.out.println("已掌握古诗数量：" + system.getMasteredPoems().size());
                System.out.println("练习次数：" + system.getStudyRecord().getExerciseResults().size());
                if (!system.getStudyRecord().getExerciseResults().isEmpty()) {
                    System.out.println("平均成绩：" + String.format("%.1f", system.getStudyRecord().getAverageScore()) + "分");
                }
            } else {
                System.out.println("未找到学习记录或加载失败，将创建新的学习记录。");
            }
            
            // 启动主菜单
            startMainMenu(system);
            
            // 退出时保存学习记录
            System.out.println("正在保存学习记录...");
            boolean saveSuccess = system.saveStudyRecord();
            
            if (saveSuccess) {
                System.out.println("学习记录保存成功！");
            } else {
                System.out.println("警告：学习记录保存失败！");
            }
            
            // 显示退出信息
            showExitMessage();
            
        } catch (Exception e) {
            System.err.println("系统发生错误：" + e.getMessage());
            e.printStackTrace();
            System.out.println("\n系统将退出...");
        }
    }
    
    // 显示欢迎信息
    private static void showWelcomeMessage() {
        System.out.println("==============================================");
        System.out.println("          欢迎使用古诗学习系统");
        System.out.println("==============================================");
        System.out.println("本系统提供古诗学习、查询和练习功能，帮助您更好地学习中国古典诗词。");
        System.out.println();
    }
    
    // 显示退出信息
    private static void showExitMessage() {
        System.out.println();
        System.out.println("==============================================");
        System.out.println("          感谢使用古诗学习系统");
        System.out.println("           下次学习之旅再见！");
        System.out.println("==============================================");
    }
    
    // 启动主菜单
    private static void startMainMenu(PoemSystem system) {
        Scanner scanner = new Scanner(System.in);
        boolean exit = false;
        
        while (!exit) {
            showMainMenu();
            int choice = getChoice(scanner);
            
            switch (choice) {
                case 1:
                    // 进入学习模式
                    startStudyMode(system);
                    break;
                case 2:
                    // 进入练习模式
                    startExerciseMode(system);
                    break;
                case 3:
                    // 显示系统统计信息
                    showSystemStats(system);
                    break;
                case 0:
                    // 退出系统
                    exit = true;
                    System.out.println("准备退出系统...");
                    break;
                default:
                    System.out.println("无效的选择，请重新输入！");
            }
        }
        
        scanner.close();
    }
    
    // 显示主菜单
    private static void showMainMenu() {
        System.out.println("\n===== 主菜单 =====");
        System.out.println("1. 学习模式");
        System.out.println("2. 练习模式");
        System.out.println("3. 系统统计");
        System.out.println("0. 退出系统");
        System.out.print("请选择功能：");
    }
    
    // 获取用户选择
    private static int getChoice(Scanner scanner) {
        int choice = -1;
        try {
            choice = scanner.nextInt();
            scanner.nextLine(); // 消耗换行符
        } catch (InputMismatchException e) {
            scanner.nextLine(); // 清除输入缓冲区
        }
        return choice;
    }
    
    // 启动学习模式
    private static void startStudyMode(PoemSystem system) {
        StudyMode studyMode = new StudyMode(system);
        studyMode.start();
    }
    
    // 启动练习模式
    private static void startExerciseMode(PoemSystem system) {
        ExerciseMode exerciseMode = new ExerciseMode(system);
        exerciseMode.start();
    }
    
    // 显示系统统计信息
    private static void showSystemStats(PoemSystem system) {
        System.out.println("\n===== 系统统计 =====");
        System.out.println("1. 古诗数据统计：");
        System.out.println("   - 总古诗数量：" + system.getAllPoems().size());
        System.out.println("   - 总诗人数量：" + system.getAllPoets().size());
        
        System.out.println("\n2. 学习进度统计：");
        System.out.println("   - 已掌握古诗数量：" + system.getMasteredPoems().size());
        double masteryRate = system.getAllPoems().isEmpty() ? 0 : 
            (double) system.getMasteredPoems().size() / system.getAllPoems().size() * 100;
        System.out.println("   - 掌握进度：" + String.format("%.1f", masteryRate) + "%");
        
        System.out.println("\n3. 练习成绩统计：");
        List<ExerciseResult> results = system.getStudyRecord().getExerciseResults();
        if (!results.isEmpty()) {
            System.out.println("   - 总练习次数：" + results.size());
            System.out.println("   - 平均成绩：" + String.format("%.1f", system.getStudyRecord().getAverageScore()) + "分");
            
            // 计算最高分和最低分
            int maxScore = Integer.MIN_VALUE;
            int minScore = Integer.MAX_VALUE;
            for (ExerciseResult result : results) {
                maxScore = Math.max(maxScore, result.getScore());
                minScore = Math.min(minScore, result.getScore());
            }
            System.out.println("   - 最高成绩：" + maxScore + "分");
            System.out.println("   - 最低成绩：" + minScore + "分");
            
            // 显示最近的5次练习记录
            System.out.println("\n   最近的5次练习记录：");
            List<ExerciseResult> recentResults = system.getStudyRecord().getRecentExerciseResults(5);
            for (int i = 0; i < recentResults.size(); i++) {
                ExerciseResult result = recentResults.get(i);
                System.out.println("   " + (i + 1) + ". " + result);
            }
        } else {
            System.out.println("   - 暂无练习记录");
        }
        
        // 等待用户按回车继续
        System.out.println("\n按回车返回主菜单...");
        new Scanner(System.in).nextLine();
    }
}