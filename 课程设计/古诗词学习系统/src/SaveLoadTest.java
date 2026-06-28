import java.util.*;

public class SaveLoadTest {
    public static void main(String[] args) {
        // 测试保存和加载学习历史功能
        System.out.println("===== 测试保存和加载学习历史功能 =====\n");
        
        // 测试步骤1：创建系统实例并加载古诗数据
        System.out.println("步骤1：创建系统实例并加载古诗数据");
        PoemSystem system1 = new PoemSystem();
        String filePath = "d:\\古诗学习系统\\poems.txt";
        int poemCount = system1.loadPoemsFromFile(filePath);
        
        if (poemCount == 0) {
            System.out.println("错误：无法加载古诗数据，测试无法继续！");
            return;
        }
        
        System.out.println("成功加载 " + poemCount + " 首古诗！");
        
        // 测试步骤2：添加一些已掌握的古诗
        System.out.println("\n步骤2：添加一些已掌握的古诗和练习记录");
        
        // 添加5首古诗到已掌握列表
        int masteredCount = 0;
        for (Poem poem : system1.getAllPoems()) {
            if (masteredCount < 5) {
                system1.addToMastered(poem);
                System.out.println("添加已掌握：《" + poem.getTitle() + "》 - " + poem.getPoet().getName());
                masteredCount++;
            }
        }
        
        // 添加3条练习记录
        ExerciseResult result1 = new ExerciseResult(10, 8, 80);
        result1.addDetail("测试练习1 - 正确率80%");
        system1.addExerciseResult(result1);
        
        ExerciseResult result2 = new ExerciseResult(10, 9, 90);
        result2.addDetail("测试练习2 - 正确率90%");
        system1.addExerciseResult(result2);
        
        ExerciseResult result3 = new ExerciseResult(10, 10, 100);
        result3.addDetail("测试练习3 - 正确率100%");
        system1.addExerciseResult(result3);
        
        System.out.println("\n添加了3条练习记录：");
        System.out.println("1. 10题中正确8题，得分80分");
        System.out.println("2. 10题中正确9题，得分90分");
        System.out.println("3. 10题中正确10题，得分100分");
        
        // 测试步骤3：保存学习记录
        System.out.println("\n步骤3：保存学习记录到文件");
        boolean saveSuccess = system1.saveStudyRecord();
        
        if (saveSuccess) {
            System.out.println("保存学习记录成功！");
        } else {
            System.out.println("保存学习记录失败！测试无法继续。");
            return;
        }
        
        // 测试步骤4：创建新的系统实例并加载学习记录
        System.out.println("\n步骤4：创建新的系统实例并加载学习记录");
        PoemSystem system2 = new PoemSystem();
        boolean loadSuccess = system2.loadStudyRecord();
        
        if (loadSuccess) {
            System.out.println("加载学习记录成功！");
        } else {
            System.out.println("加载学习记录失败！");
            return;
        }
        
        // 测试步骤5：验证加载的数据是否正确
        System.out.println("\n步骤5：验证加载的数据是否正确");
        
        // 验证已掌握古诗数量
        List<Poem> masteredPoems = system2.getMasteredPoems();
        System.out.println("\n已掌握古诗数量：" + masteredPoems.size());
        if (masteredPoems.size() == 5) {
            System.out.println("✓ 已掌握古诗数量正确");
        } else {
            System.out.println("✗ 已掌握古诗数量错误，应为5个，实际为" + masteredPoems.size() + "个");
        }
        
        // 验证练习记录
        List<ExerciseResult> exerciseResults = system2.getStudyRecord().getExerciseResults();
        System.out.println("\n练习记录数量：" + exerciseResults.size());
        if (exerciseResults.size() == 3) {
            System.out.println("✓ 练习记录数量正确");
        } else {
            System.out.println("✗ 练习记录数量错误，应为3条，实际为" + exerciseResults.size() + "条");
        }
        
        // 验证练习记录的内容
        if (exerciseResults.size() >= 3) {
            ExerciseResult loadedResult1 = exerciseResults.get(0);
            ExerciseResult loadedResult2 = exerciseResults.get(1);
            ExerciseResult loadedResult3 = exerciseResults.get(2);
            
            System.out.println("\n练习记录详情：");
            System.out.println("1. " + loadedResult1);
            System.out.println("2. " + loadedResult2);
            System.out.println("3. " + loadedResult3);
            
            // 验证得分
            boolean scoresCorrect = (loadedResult1.getScore() == 80 && 
                                    loadedResult2.getScore() == 90 && 
                                    loadedResult3.getScore() == 100);
            
            if (scoresCorrect) {
                System.out.println("✓ 练习记录得分正确");
            } else {
                System.out.println("✗ 练习记录得分错误");
            }
            
            // 验证平均成绩
            double averageScore = system2.getStudyRecord().getAverageScore();
            System.out.println("\n平均成绩：" + averageScore + "分");
            if (Math.abs(averageScore - 90.0) < 0.01) {
                System.out.println("✓ 平均成绩正确");
            } else {
                System.out.println("✗ 平均成绩错误，应为90.0分");
            }
        }
        
        // 测试步骤6：测试在已加载记录的基础上添加新内容并保存
        System.out.println("\n步骤6：在已加载记录的基础上添加新内容并保存");
        
        // 添加一条新的练习记录
        ExerciseResult newResult = new ExerciseResult(10, 7, 70);
        newResult.addDetail("测试练习4 - 正确率70%");
        system2.addExerciseResult(newResult);
        System.out.println("添加了一条新的练习记录：10题中正确7题，得分70分");
        
        // 再次保存
        saveSuccess = system2.saveStudyRecord();
        if (saveSuccess) {
            System.out.println("保存更新后的学习记录成功！");
        }
        
        // 再次加载以验证更新
        PoemSystem system3 = new PoemSystem();
        loadSuccess = system3.loadStudyRecord();
        if (loadSuccess) {
            List<ExerciseResult> updatedResults = system3.getStudyRecord().getExerciseResults();
            System.out.println("\n更新后练习记录数量：" + updatedResults.size());
            if (updatedResults.size() == 4) {
                System.out.println("✓ 更新后练习记录数量正确");
            } else {
                System.out.println("✗ 更新后练习记录数量错误");
            }
            
            // 验证新的平均成绩
            double newAverageScore = system3.getStudyRecord().getAverageScore();
            System.out.println("更新后平均成绩：" + newAverageScore + "分");
        }
        
        System.out.println("\n===== 保存和加载学习历史功能测试完成 =====");
    }
}