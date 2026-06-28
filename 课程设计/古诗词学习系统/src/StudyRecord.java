import java.io.Serializable;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class StudyRecord implements Serializable {
    private Date date;                // 学习日期
    private List<Poem> masteredPoems; // 已掌握的古诗列表
    private List<ExerciseResult> exerciseResults; // 练习成绩列表

    public StudyRecord() {
        this.date = new Date();
        this.masteredPoems = new ArrayList<>();
        this.exerciseResults = new ArrayList<>();
    }

    public StudyRecord(Date date) {
        this.date = date;
        this.masteredPoems = new ArrayList<>();
        this.exerciseResults = new ArrayList<>();
    }

    // 添加已掌握的古诗
    public void addMasteredPoem(Poem poem) {
        if (!masteredPoems.contains(poem)) {
            masteredPoems.add(poem);
        }
    }

    // 移除已掌握的古诗
    public void removeMasteredPoem(Poem poem) {
        masteredPoems.remove(poem);
    }

    // 检查古诗是否已掌握
    public boolean isPoemMastered(Poem poem) {
        return masteredPoems.contains(poem);
    }

    // 添加练习结果
    public void addExerciseResult(ExerciseResult result) {
        exerciseResults.add(result);
    }

    // 获取最近的练习结果
    public List<ExerciseResult> getRecentExerciseResults(int count) {
        int startIndex = Math.max(0, exerciseResults.size() - count);
        return new ArrayList<>(exerciseResults.subList(startIndex, exerciseResults.size()));
    }

    // 获取平均成绩
    public double getAverageScore() {
        if (exerciseResults.isEmpty()) {
            return 0;
        }
        double totalScore = 0;
        for (ExerciseResult result : exerciseResults) {
            totalScore += result.getScore();
        }
        return totalScore / exerciseResults.size();
    }

    // getter and setter methods
    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public List<Poem> getMasteredPoems() {
        return masteredPoems;
    }

    public void setMasteredPoems(List<Poem> masteredPoems) {
        this.masteredPoems = masteredPoems;
    }

    public List<ExerciseResult> getExerciseResults() {
        return exerciseResults;
    }

    public void setExerciseResults(List<ExerciseResult> exerciseResults) {
        this.exerciseResults = exerciseResults;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("学习记录 (").append(date).append(")\n");
        sb.append("已掌握古诗数量：").append(masteredPoems.size()).append("\n");
        sb.append("练习次数：").append(exerciseResults.size()).append("\n");
        if (!exerciseResults.isEmpty()) {
            sb.append("平均成绩：").append(String.format("%.1f", getAverageScore())).append("分\n");
        }
        return sb.toString();
    }
}

// 练习结果类
class ExerciseResult implements Serializable {
    private Date date;          // 练习日期
    private int totalQuestions; // 总题目数
    private int correctCount;   // 正确数量
    private int score;          // 得分
    private List<String> details; // 详细记录

    public ExerciseResult(int totalQuestions, int correctCount, int score) {
        this.date = new Date();
        this.totalQuestions = totalQuestions;
        this.correctCount = correctCount;
        this.score = score;
        this.details = new ArrayList<>();
    }

    // 添加详细记录
    public void addDetail(String detail) {
        details.add(detail);
    }

    // getter and setter methods
    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public int getTotalQuestions() {
        return totalQuestions;
    }

    public void setTotalQuestions(int totalQuestions) {
        this.totalQuestions = totalQuestions;
    }

    public int getCorrectCount() {
        return correctCount;
    }

    public void setCorrectCount(int correctCount) {
        this.correctCount = correctCount;
    }

    public int getScore() {
        return score;
    }

    public void setScore(int score) {
        this.score = score;
    }

    public List<String> getDetails() {
        return details;
    }

    public void setDetails(List<String> details) {
        this.details = details;
    }

    @Override
    public String toString() {
        return "练习结果 (" + date + ")：" + correctCount + "/" + totalQuestions + " 正确，得分：" + score + "分";
    }
}